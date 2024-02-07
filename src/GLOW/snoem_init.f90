subroutine snoem_init(data_dir, snoem_zin, snoem_mlatin, snoem_no_mean, snoem_eofs)    
    implicit none

    character(1024)::data_dir
    real,dimension(16),intent(out)::snoem_zin
    real,dimension(33),intent(out)::snoem_mlatin
    real,dimension(33,16),intent(out)::snoem_no_mean
    real,dimension(33,16,3),intent(out)::snoem_eofs

    character(len=1024) :: filepath
    integer :: j,k,n

    filepath = trim(data_dir)//'snoem_eof.dat'
    open(unit=1,file=filepath,status='old',action='read')
    read(1,*) (snoem_zin(k),k=1,16)
    read(1,*) (snoem_mlatin(j),j=1,33)
    read(1,*) ((snoem_no_mean(j,k),j=1,33),k=1,16)
    read(1,*) (((snoem_eofs(j,k,n),j=1,33),k=1,16),n=1,3)
    close(unit=1)


    end subroutine snoem_init