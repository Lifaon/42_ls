#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

int main ( int argc, char ** argv ) {
	int	 i;
	char	mode[10];
	char	*time;
	struct stat st;
	struct passwd *pw;
	struct group *gr;


	for (i = 1; i < argc; ++i) {
		if (stat(argv[i], &st))
			perror(argv[i]);
		else {
			mode[0] = '-';
			mode[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
			mode[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
			mode[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';
			mode[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
			mode[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
			mode[6] = (st.st_mode & S_IXGRP) ? 'x' : '-';
			mode[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
			mode[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
			mode[9] = (st.st_mode & S_IXOTH) ? 'x' : '-';
			pw = getpwuid(st.st_uid);
			gr = getgrgid(st.st_gid);
			time = ctime(&st.st_mtim.tv_sec);
			// time[strlen(time) - 1] = '\0';
			printf("%10.10s %ld %s %s %ld %.12s %s\n", \
				mode, st.st_nlink, pw->pw_name, gr->gr_name, \
				st.st_size, time + 4, argv[i]);
		}
	}
	return 0;
}
