subroutine cglow_init(jmax,nbins,iscale,data_dir, &
    vcb, &
    zz, zo, zn2, zo2, zno, zns, znd, zrho, ze, &
    ztn, zti, zte, eheat, tez, ecalc, tei, tpi, tir, &
    phitop, ener, edel, &
    wave1, wave2, sflux, sf_rflux, sf_scale1, sf_scale2, &
    pespec, sespec, uflx, dflx, &
    zmaj, zcol, pia, sion, &
    photoi, photod, phono, &
    epsil1, epsil2, ephoto_prob, &
    sigion, sigabs, &
    aglw, &
    zxden, &
    zeta, &
    zceta, &
    zlbh, &
    sigs, pe, pin, &
    sigex, sigix, &
    siga, sec, &
    iimaxx, &
    ww, ao, omeg, anu, bb, auto, thi, ak, aj, ts, ta, tb, gams, gamb, &
    production, loss, &
    snoem_zin, snoem_mlatin, snoem_no_mean, snoem_eofs)

    use, intrinsic :: iso_fortran_env, only: wp=>real32

    implicit none
    save

!! Array dimensions, configurable:

    integer,intent(in) :: jmax              ! number of vertical levels
    integer,intent(in) :: nbins             ! number of energetic electron energy bins
    integer,intent(in) :: iscale            ! solar flux scaling factor
    character(1024),intent(in) :: data_dir  ! directory containing data files needed by glow subroutines

    integer,parameter :: lmax=123  ! number of wavelength intervals for solar flux
    integer,parameter :: nmaj=3    ! number of major species
    integer,parameter :: nst=6     ! number of states produced by photoionization/dissociation
    integer,parameter :: nei=10    ! number of states produced by electron impact
    integer,parameter :: nex=12    ! number of excited/ionized species
    integer,parameter :: nw=15     ! number of airglow emission wavelengths
    integer,parameter :: nc=10     ! number of component production terms for each emission

    ! Directory containing data files needed by glow subroutines:

    real,allocatable,dimension(:),intent(out) :: vcb ! (nw)

    real,allocatable,dimension(:),intent(out) ::             &                   ! (jmax)
        zz, zo, zn2, zo2, zno, zns, znd, zrho, ze, &
        ztn, zti, zte, eheat, tez, ecalc, tei, tpi, tir
    real(wp),allocatable,dimension(:),intent(out)     :: phitop, ener, edel           ! (nbins)
    real,allocatable,dimension(:),intent(out)     :: wave1, wave2, sflux         ! (lmax)
    real,allocatable,dimension(:) ,intent(out)    :: sf_rflux, sf_scale1, sf_scale2 ! (lmax)
    real,allocatable,dimension(:,:) ,intent(out)  :: pespec, sespec, uflx, dflx  ! (nbins,jmax)
    real,allocatable,dimension(:,:) ,intent(out)  :: zmaj, zcol, pia, sion       ! (nmaj,jmax)
    real,allocatable,dimension(:,:,:) ,intent(out):: photoi, photod              ! (nst,nmaj,jmax)
    real,allocatable,dimension(:,:) ,intent(out)  :: phono                       ! (nst,jmax)
    real,allocatable,dimension(:,:,:),intent(out) :: epsil1, epsil2, ephoto_prob ! (nst,nmaj,lmax)
    real,allocatable,dimension(:,:)   ,intent(out):: sigion, sigabs              ! (nmaj,lmax)
    real,allocatable,dimension(:,:,:),intent(out) :: aglw                        ! (nei,nmaj,jmax)
    real,allocatable,dimension(:,:),intent(out)   :: zxden                       ! (nex,jmax)
    real(wp),allocatable,dimension(:,:),intent(out)   :: zeta                        ! (nw,jmax)
    real,allocatable,dimension(:,:,:),intent(out) :: zceta                       ! (nc,nw,jmax)
    real,allocatable,dimension(:,:) ,intent(out)  :: zlbh                        ! (nc,jmax)
    real,allocatable,dimension(:,:)  ,intent(out) :: sigs,pe,pin                 ! (nmaj,nbins)
    real,allocatable,dimension(:,:,:) ,intent(out):: sigex,sigix                 ! (nei,nmaj,nbins)
    real,allocatable,dimension(:,:,:) ,intent(out):: siga,sec                    ! (nei,nbins,nbins)
    integer,allocatable,dimension(:) ,intent(out) :: iimaxx                      ! (nbins)
    real,allocatable,dimension(:,:) ,intent(out):: &                             ! (nei,nmaj)
        ww,ao,omeg,anu,bb,auto,thi,ak,aj,ts,ta,tb,gams,gamb

    real(wp), allocatable, dimension(:,:) ,intent(out) :: production, loss  ! gchem.f90

    real,allocatable,dimension(:),intent(out) :: snoem_zin          ! altitude grid (16)
    real,allocatable,dimension(:),intent(out) :: snoem_mlatin       ! magnetic latitude grid (33)
    real,allocatable,dimension(:,:),intent(out) :: snoem_no_mean   ! mean nitric oxide distribution (33,16)
    real,allocatable,dimension(:,:,:),intent(out) :: snoem_eofs    ! empirical orthogonal functions (33,16,3)

    ! Allocate variable arrays:
    
        allocate        &
          (zz   (jmax), &
           zo   (jmax), &
           zn2  (jmax), &
           zo2  (jmax), &
           zno  (jmax), &
           zns  (jmax), &
           znd  (jmax), &
           zrho (jmax), &
           ze   (jmax), &
           ztn  (jmax), &
           zti  (jmax), &
           zte  (jmax), &
           eheat(jmax), &
           tez  (jmax), &
           tei  (jmax), &
           tpi  (jmax), &
           tir  (jmax), &
           ecalc(jmax))
    
        allocate            &
          (zxden(nex,jmax), &
           zeta(nw,jmax),   &
           zceta(nc,nw,jmax), &
           zlbh(nc,jmax))
    
        if (.not.allocated(production))allocate(production(NEX,JMAX))
        if (.not.allocated(loss))allocate(loss(NEX,JMAX))
    
        if (.not.allocated(phitop)) allocate(phitop(nbins))
        if (.not.allocated(ener)) allocate(ener(nbins))
        if (.not.allocated(edel)) allocate(edel(nbins))
    
        allocate           &
          (wave1(lmax),    &
           wave2(lmax),    &
           sflux(lmax),    &
           sf_rflux(lmax),    &
           sf_scale1(lmax),&
           sf_scale2(lmax))
    
        allocate               &
          (pespec(nbins,jmax), &
           sespec(nbins,jmax), &
           uflx  (nbins,jmax), &
           dflx  (nbins,jmax))
    
        allocate &
          (zmaj(nmaj,jmax), &
           zcol(nmaj,jmax), &
           pia (nmaj,jmax), &
           sion(nmaj,jmax))
    
        allocate &
          (aglw  (nei,nmaj,jmax), &
           photoi(nst,nmaj,jmax), &
           photod(nst,nmaj,jmax), &
           epsil1(nst,nmaj,lmax), &
           epsil2(nst,nmaj,lmax), &
           ephoto_prob(nst,nmaj,lmax), &
           sigion(nmaj,lmax),     &
           sigabs(nmaj,lmax),     &
           phono(nst,jmax))
    
        allocate             &
          (sigs(nmaj,nbins), &
           pe  (nmaj,nbins), &
           pin (nmaj,nbins))
    
        allocate                  &
          (sigex(nei,nmaj,nbins), &
           sigix(nei,nmaj,nbins))
    
        allocate                  &
          (siga(nei,nbins,nbins), &
           sec (nei,nbins,nbins))
    
        allocate(iimaxx(nbins))
    
        allocate           &
          (ww  (nei,nmaj), &
           ao  (nei,nmaj), &
           omeg(nei,nmaj), &
           anu (nei,nmaj), &
           bb  (nei,nmaj), &
           auto(nei,nmaj), &
           thi (nei,nmaj), &
           ak  (nei,nmaj), &
           aj  (nei,nmaj), &
           ts  (nei,nmaj), &
           ta  (nei,nmaj), &
           tb  (nei,nmaj), &
           gams(nei,nmaj), &
           gamb(nei,nmaj))

        allocate(snoem_zin(16))
        allocate(snoem_mlatin(33))
        allocate(snoem_no_mean(33,16))
        allocate(snoem_eofs(33,16,3))
        allocate(vcb(nw))
    
    ! Zero all allocated variable arrays:
    
           production(:,:) = 0.
           loss(:,:) = 0.
    
           zz   (:)     =0.
           zo   (:)     =0.
           zn2  (:)     =0.
           zo2  (:)     =0.
           zno  (:)     =0.
           zns  (:)     =0.
           znd  (:)     =0.
           zrho (:)     =0.
           ze   (:)     =0.
           ztn  (:)     =0.
           zti  (:)     =0.
           zte  (:)     =0.
           eheat(:)     =0.
           tez  (:)     =0.
           tei  (:)     =0.
           tpi  (:)     =0.
           tir  (:)     =0.
           ecalc(:)     =0.
           zxden(:,:)   =0.
           zeta(:,:)    =0.
           zceta(:,:,:) =0.
           zlbh(:,:)    =0.
           phitop(:)    =0.
           ener  (:)    =0.
           edel   (:)    =0.
           wave1(:)     =0.
           wave2(:)     =0.
           sflux(:)     =0.
           sf_rflux(:)  =0.
           sf_scale1(:) =0.
           sf_scale2(:) =0.
           pespec(:,:)  =0.
           sespec(:,:)  =0.
           uflx  (:,:)  =0.
           dflx  (:,:)  =0.
           zmaj(:,:)    =0.
           zcol(:,:)    =0.
           pia (:,:)    =0.
           sion(:,:)    =0.
           aglw  (:,:,:)=0.
           photoi(:,:,:)=0.
           photod(:,:,:)=0.
           phono(:,:)   =0.
           epsil1(:,:,:) =0.
           epsil2(:,:,:) =0.
           ephoto_prob(:,:,:) =0.
           sigabs(:,:)    =0.
           sigion(:,:)    =0.
           sigs(:,:)    =0.
           pe  (:,:)    =0.
           pin (:,:)    =0.
           sigex(:,:,:) =0.
           sigix(:,:,:) =0.
           siga(:,:,:)  =0.
           sec (:,:,:)  =0.
           iimaxx(:)    =0.
           ww  (:,:)    =0.
           ao  (:,:)    =0.
           omeg(:,:)    =0.
           anu (:,:)    =0.
           bb  (:,:)    =0.
           auto(:,:)    =0.
           thi (:,:)    =0.
           ak  (:,:)    =0.
           aj  (:,:)    =0.
           ts  (:,:)    =0.
           ta  (:,:)    =0.
           tb  (:,:)    =0.
           gams(:,:)    =0.
           gamb(:,:)    =0.
           snoem_zin(:) =0.
           snoem_mlatin(:) =0.
           snoem_no_mean(:,:) =0.
           snoem_eofs(:,:,:) =0.
           vcb(:) =0.
    
           call egrid(ener, edel, nbins)  ! initialize energy grid
           call snoem_init(data_dir, snoem_zin, snoem_mlatin, snoem_no_mean, snoem_eofs)! initialize snoem
           call ssflux_init(iscale,lmax,data_dir,wave1,wave2,sf_rflux,sf_scale1,sf_scale2)       ! initialize ssflux
           call ephoto_init(lmax,nmaj,nst, &
           wave1,wave2, &
           epsil1,epsil2,ephoto_prob, &
           sigion,sigabs, &
           data_dir)             ! initialize ephoto
           call EXSECT(ener, edel, nbins, &
           ww,ao,omeg,anu,bb,auto,thi,ak,aj,ts,ta,tb,gams,gamb, &
           sigs,pe,pin,sigex,sigix,siga,sec,iimaxx) ! call exsect
    
      end subroutine cglow_init