subroutine msis_wrap(jmax,idate,ut,glat,glon,stl,f107a,f107p,ap, &
    z,zo,zn2,zo2,zns,ztn,znd)

    implicit none
    integer, intent(in) :: jmax,idate
    real, intent(in) :: ut,glat,glon,stl,f107a,f107p,ap
    real, dimension(jmax), intent(in) :: z ! z is the altitude in km
    real, dimension(jmax), intent(inout) :: zo,zn2,zo2,zns,ztn,znd ! output, density in cm^-3

    integer:: j
    real :: d(8), t(2), sw(25)

    data sw/25*1./

    call tselec(sw)

    do j=1,jmax
        call gtd7(idate,ut,z(j),glat,glon,stl,f107a,f107p,ap,48,d,t)
        zo(j) = d(2)
        zn2(j) = d(3)
        zo2(j) = d(4)
        zns(j) = d(8)
        ztn(j) = t(2)
        znd(j) = 0.
    end do

end subroutine msis_wrap
