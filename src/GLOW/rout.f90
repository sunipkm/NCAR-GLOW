! Subroutine ROUT writes model atmosphere and excitation rates to an output file
! in order to transfer them to Randy Gladstone's REDISTER radiative transfer program.

! This software is part of the GLOW model.  Use is governed by the Open Source
! Academic Research License Agreement contained in the file glowlicense.txt.
! For more information see the file glow.txt.

! Scott Baily and Stan Solomon, 9/1994
! Replaced 834 with LBH, SCS, 2/2003
! Reduced cascade contribution to 1356, SCS, 9/2003
! Included radiative recombination in 1356, SCS, 9/2003
! Refactored to f90, SCS, 12/2016
! Changed 1356, 1304, and LBH to use volume emission rate arrays, SCS, 12/2016


    SUBROUTINE ROUT(ROFILE,LUN,EF,EZ,ITAIL,FRACO,FRACO2,FRACN2, &
      JMAX,NEI,NMAJ,NEX,NW,&
      IDATE,UT,GLAT,GLONG,F107,F107P,F107A,SZA,DIP,XUVFAC, &
      ZZ,ZTN,ZTI,ZTE,ZO,ZO2,ZNS,ZN2,ECALC,AGLW,ZXDEN,ZETA)

      use, intrinsic :: iso_fortran_env, only: wp => real32

      implicit none

      integer,intent(in)::jmax,idate,nei,nmaj,nex,nw
      real,intent(in)::ut,glat,glong,f107,f107p,f107a,sza,dip,xuvfac
      real,dimension(jmax),intent(inout)::zz,ztn,zti,zte,zo,zo2,zns,zn2,ecalc
      real,dimension(nei,nmaj,jmax),intent(inout)::aglw
      real,dimension(nex,jmax),intent(inout)::zxden
      real(wp),dimension(nw,jmax),intent(inout)::zeta

      integer,intent(in) :: lun,itail
      real,intent(in) :: ef,ez,fraco,fraco2,fracn2
      character(len=40),intent(in) :: rofile

      real,dimension(jmax)::z,zhe,e1356,e1304,e1027,e989,elbh
      integer :: j

      do j=1,jmax
        z(j)=zz(j)/1.e5
        zhe(j)=0.
        e1356(j)=zeta(13,j)
        e1304(j)=zeta(14,j)
        e1027(j)=aglw(7,1,j)
        e989(j)=aglw(8,1,j)
        elbh(j)=zeta(12,j)
      enddo

      open(unit=lun,file=rofile,status='unknown')

      write(lun,"('   JMAX ','   SZA  ','   UT   ','   IDATE','   LAT  ','   LONG ','    DIP ')")
      write(lun,"(i8,f8.2,f8.1,i8,3f8.2)") jmax,sza*180./3.14159,ut,idate,glat,glong,dip
      write(lun,"('  F107  ','  F107p ','  F107a ',' XUVfac ')")
      write(lun,"(4f8.2)") f107,f107p,f107a,xuvfac
      write(lun,"(' Eflux  ',' Ezero  ',' Itail  ',' FracO  ',' FracO2  ',' FracN2  ')")
      write(lun,"(f8.2,f8.1,i8,3f8.2)") ef, ez, itail, fraco, fraco2, fracn2
      write(lun,"(' Alt    Tn    Ti    Te      O        O2       N2       He       N        Ne       O+      1356     1304     1027      989     LBH')")

      do j=1,jmax
        write(lun,"(0p,f6.1,3f6.0,1p,12e9.2)") &
          z(j),ztn(j),zti(j),zte(j),zo(j),zo2(j),zn2(j),zhe(j), &
          zns(j),ecalc(j),zxden(3,j),e1356(j),e1304(j),e1027(j),e989(j),elbh(j)
      enddo

      close(lun)
      return

    end subroutine rout
