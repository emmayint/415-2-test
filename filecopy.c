#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//You may also add more include directives as well.

//THIS VALUE CANNOT BE CHANGED.
//You should use this value when creating your buffer.
// And also to limit the amount each read CAN do.
#define BUFF_MAX 13
#define FILENAME_SIZE 200

int
main(int argc, char const *argv[])
{
	char src_file_name[FILENAME_SIZE]; // ??? must initialize with size?
	char dest_file_name[FILENAME_SIZE];
    int count = 0;
    char buffer[BUFF_MAX];

	printf("%s", "Welcome to the File Copy Program by Ting! \nEnter the name of the file to copy from:\n");
	scanf("%s", src_file_name); // ?? %[^\n]???
    //open source file as read only and chech file descriptor
    int src_fd = open(src_file_name, O_RDONLY);
    if (src_fd <0) {
        printf("error: open %s \n", src_file_name);
        return -1;
    }
    
    printf("%s", "Enter the name of the file to copy to:\n");
    scanf("%s", dest_file_name); // ?? %[^\n]???
    //open/crate destination file and chech file descriptor
    int dest_fd = open(dest_file_name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (dest_fd <0) {
        printf("error: open %s \n", dest_file_name);
        return -1;
    }
    
    // copy from source file to destination file with buffer.
    while (1) {
        int bytes_read = read(src_fd, buffer, sizeof(buffer));
        if (bytes_read <0) {
            printf("error: read %s \n", src_file_name);
            return -1;
        //at or past the end of file, nobytes are read, and read() returns 0.
        }else if (bytes_read == 0) {
            printf("%s%d%s\n", "File Copy Successful, ", count, " bytes copied");
            break;
        //On success, the number of bytes read is returned (0 indicates end of file)
        }else if (bytes_read > 0) {
            //On success, the number of bytes written is returned
            //(0 indicates nothing was written). On error, -1 is returned
            int bytes_written = write(dest_fd, buffer, bytes_read);
            if (bytes_written != bytes_read) {
                printf("write %s error\n", dest_file_name);
                return -1;
            }
            count += bytes_read;
        }
    }
    if(close(src_fd) < 0){
        printf("error: close %s \n", src_file_name);
        return -1; // -1 or 1?
    }
    if(close(dest_fd) < 0){
        printf("error: close %s \n", dest_file_name);
        return -1;
    }
	return 0;
}


