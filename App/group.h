#ifndef _GROUP_
#define _GROUP_

struct group
{
		char *gr_name;		/* Group name.	*/
		char *gr_passwd;		/* Password.	*/
		unsigned int gr_gid;		/* Group ID.	*/
		char **gr_mem;		/* Member list.	*/
};
#endif