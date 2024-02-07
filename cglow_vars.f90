module cglow_data
  character(1024) :: data_dir

  integer :: jmax, lmax, nmaj, nst, nbins, nei, nex, nw, nc

  integer :: idate,iscale,jlocal,kchem,ierr
  real    :: ut,glat,glong,f107,f107a,f107p,ap,ef,ec
  real    :: xuvfac, sza, dip, efrac
  real,dimension(nw) :: vcb

  real,dimension(jmax) :: &
  zz, zo, zn2, zo2, zno, zns, znd, zrho, ze, &
    ztn, zti, zte, eheat, tez, ecalc, tei, tpi, tir
  real(wp),dimension(nbins)     :: phitop, ener, edel           ! (nbins)
  real,dimension(lmax)     :: wave1, wave2, sflux         ! (lmax)
  real,dimension(lmax)     :: sf_rflux, sf_scale1, sf_scale2 ! (lmax)
  real,dimension(nbins,jmax)   :: pespec, sespec, uflx, dflx  ! (nbins,jmax)
  real,dimension(nmaj,jmax)   :: zmaj, zcol, pia, sion       ! (nmaj,jmax)
  real,dimension(nst,nmaj,jmax) :: photoi, photod              ! (nst,nmaj,jmax)
  real,dimension(nst,jmax)   :: phono                       ! (nst,jmax)
  real,dimension(nst,nmaj,lmax) :: epsil1, epsil2, ephoto_prob ! (nst,nmaj,lmax)
  real,dimension(nmaj,lmax)   :: sigion, sigabs              ! (nmaj,lmax)
  real,dimension(nei,nmaj,jmax) :: aglw                        ! (nei,nmaj,jmax)
  real,dimension(nex,jmax)   :: zxden                       ! (nex,jmax)
  real(wp),dimension(nw,jmax)   :: zeta                        ! (nw,jmax)
  real,dimension(nc,nw,jmax) :: zceta                       ! (nc,nw,jmax)
  real,dimension(nc,jmax)   :: zlbh                        ! (nc,jmax)
  real,dimension(nmaj,nbins)   :: sigs,pe,pin                 ! (nmaj,nbins)
  real,dimension(nei,nmaj,nbins) :: sigex,sigix                 ! (nei,nmaj,nbins)
  real,dimension(nei,nbins,nbins) :: siga,sec                    ! (nei,nbins,nbins)
  
  integer,dimension(nbins)  :: iimaxx                      ! (nbins)
  
  real,dimension(nei,nmaj) :: ww,ao,omeg,anu,bb,auto,thi,ak,aj,ts,ta,tb,gams,gamb

  real(wp), dimension(nex,jmax) :: production, loss  ! gchem.f90

!   real :: snoem_zin(16)          ! altitude grid
!   real :: snoem_mlatin(33)       ! magnetic latitude grid
!   real :: snoem_no_mean(33,16)   ! mean nitric oxide distribution
!   real :: snoem_eofs(33,16,3)    ! empirical orthogonal functions

end module cglow_data