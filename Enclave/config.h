/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if account management tools should be installed setuid and
   authenticate the callers */
/* #undef ACCT_TOOLS_SETUID */

/* Define to support lastlog. */
#define ENABLE_LASTLOG 1

/* Define to manage session support with logind. */
/* #undef ENABLE_LOGIND */

/* Define to 1 if translation of program messages to the user's native
   language is requested. */
#define ENABLE_NLS 1

/* Define to support the subordinate IDs. */
#define ENABLE_SUBIDS 1

/* Path for faillog file. */
#define FAILLOG_FILE "/var/log/faillog"

/* Define to the type of elements in the array set by `getgroups'. Usually
   this is either `int' or `gid_t'. */
#define GETGROUPS_T gid_t

/* max group name length */
#define GROUP_NAME_MAX_LENGTH 32

/* Define to 1 if you have the declaration of 'pam_fail_delay' */
/* #undef HAS_PAM_FAIL_DELAY */

/* Defined to 1 if you have the declaration of 'secure_getenv' */
#define HAS_SECURE_GETENV 1

/* Define to 1 if you have the <acl/libacl.h> header file. */
/* #undef HAVE_ACL_LIBACL_H */

/* Define to 1 if you have the `arc4random_buf' function. */
/* #undef HAVE_ARC4RANDOM_BUF */

/* Define to 1 if you have the <attr/error_context.h> header file. */
/* #undef HAVE_ATTR_ERROR_CONTEXT_H */

/* Define to 1 if you have the <attr/libattr.h> header file. */
/* #undef HAVE_ATTR_LIBATTR_H */

/* Define to 1 if you have the Mac OS X function CFLocaleCopyCurrent in the
   CoreFoundation framework. */
/* #undef HAVE_CFLOCALECOPYCURRENT */

/* Define to 1 if you have the Mac OS X function CFPreferencesCopyAppValue in
   the CoreFoundation framework. */
/* #undef HAVE_CFPREFERENCESCOPYAPPVALUE */

/* Define to 1 if you have the <crypt.h> header file. */
#define HAVE_CRYPT_H 1

/* Define if the GNU dcgettext() function is already present or preinstalled.
   */
#define HAVE_DCGETTEXT 1

/* Define to 1 if you have the declaration of `PAM_DATA_SILENT', and to 0 if
   you don't. */
/* #undef HAVE_DECL_PAM_DATA_SILENT */

/* Define to 1 if you have the declaration of `PAM_DELETE_CRED', and to 0 if
   you don't. */
/* #undef HAVE_DECL_PAM_DELETE_CRED */

/* Define to 1 if you have the declaration of `PAM_ESTABLISH_CRED', and to 0
   if you don't. */
/* #undef HAVE_DECL_PAM_ESTABLISH_CRED */

/* Define to 1 if you have the declaration of `PAM_NEW_AUTHTOK_REQD', and to 0
   if you don't. */
/* #undef HAVE_DECL_PAM_NEW_AUTHTOK_REQD */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the `explicit_bzero' function. */
#define HAVE_EXPLICIT_BZERO 1

/* Defined to 1 if you have the declaration of 'fgetpwent_r' */
#define HAVE_FGETPWENT_R 1

/* Define to 1 if you have the `futimes' function. */
#define HAVE_FUTIMES 1

/* Define to 1 if you have the `getentropy' function. */
#define HAVE_GETENTROPY 1

/* Define to 1 if you have the `getrandom' function. */
#define HAVE_GETRANDOM 1

/* Define to 1 if you have the `getspnam' function. */
#define HAVE_GETSPNAM 1

/* Define to 1 if you have the `getspnam_r' function. */
#define HAVE_GETSPNAM_R 1

/* Define if the GNU gettext() function is already present or preinstalled. */
#define HAVE_GETTEXT 1

/* Define to 1 if you have the `getusershell' function. */
#define HAVE_GETUSERSHELL 1

/* Define to 1 if you have the <gshadow.h> header file. */
#define HAVE_GSHADOW_H 1

/* Define if you have the iconv() function and it works. */
/* #undef HAVE_ICONV */

/* Define to 1 if you have the `initgroups' function. */
#define HAVE_INITGROUPS 1

/* Define to 1 if you have the `innetgr' function. */
#define HAVE_INNETGR 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <lastlog.h> header file. */
#define HAVE_LASTLOG_H 1

/* Define to 1 if you have the `lckpwdf' function. */
#define HAVE_LCKPWDF 1

/* Defined if you have libcrack. */
/* #undef HAVE_LIBCRACK */

/* Defined if you have the ts&szs cracklib. */
/* #undef HAVE_LIBCRACK_HIST */

/* Defined if it includes *Pw functions. */
/* #undef HAVE_LIBCRACK_PW */

/* Define to 1 if you have the <linux/btrfs_tree.h> header file. */
#define HAVE_LINUX_BTRFS_TREE_H 1

/* Define to 1 if you have the <linux/magic.h> header file. */
#define HAVE_LINUX_MAGIC_H 1

/* Define if struct lastlog has ll_host */
#define HAVE_LL_HOST 1

/* Define to 1 if you have the `lutimes' function. */
#define HAVE_LUTIMES 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset_explicit' function. */
/* #undef HAVE_MEMSET_EXPLICIT */

/* Define to 1 if you have the <paths.h> header file. */
#define HAVE_PATHS_H 1

/* Define to 1 if you have the `putgrent' function. */
#define HAVE_PUTGRENT 1

/* Define to 1 if you have the `putpwent' function. */
#define HAVE_PUTPWENT 1

/* Define to 1 if you have the `putspent' function. */
#define HAVE_PUTSPENT 1

/* Define to 1 if you have the <readpassphrase.h> header file. */
#define HAVE_READPASSPHRASE_H 1

/* Define to 1 if you have the <rpc/key_prot.h> header file. */
#define HAVE_RPC_KEY_PROT_H 1

/* Define to 1 if you have the `rpmatch' function. */
#define HAVE_RPMATCH 1

/* Define to 1 if you have the <security/openpam.h> header file. */
/* #undef HAVE_SECURITY_OPENPAM_H */

/* Define to 1 if you have the <security/pam_misc.h> header file. */
/* #undef HAVE_SECURITY_PAM_MISC_H */

/* Define to 1 if you have the <selinux/selinux.h> header file. */
/* #undef HAVE_SELINUX_SELINUX_H */

/* Define to 1 if you have the <semanage/semanage.h> header file. */
/* #undef HAVE_SEMANAGE_SEMANAGE_H */

/* Define to 1 if you have the `setgroups' function. */
#define HAVE_SETGROUPS 1

/* Define to 1 if you have the `sgetgrent' function. */
/* #undef HAVE_SGETGRENT */

/* Define to 1 if you have the `sgetpwent' function. */
/* #undef HAVE_SGETPWENT */

/* Define to 1 if you have the `sgetspent' function. */
#define HAVE_SGETSPENT 1

/* Define to 1 if you have the <sgtty.h> header file. */
#define HAVE_SGTTY_H 1

/* Have working shadow group support in libc */
#define HAVE_SHADOWGRP 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `stpecpy' function. */
/* #undef HAVE_STPECPY */

/* Define to 1 if you have the `stpeprintf' function. */
/* #undef HAVE_STPEPRINTF */

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if `ut_addr' is a member of `struct utmp'. */
#define HAVE_STRUCT_UTMP_UT_ADDR 1

/* Define to 1 if `ut_addr_v6' is a member of `struct utmp'. */
#define HAVE_STRUCT_UTMP_UT_ADDR_V6 1

/* Define to 1 if `ut_host' is a member of `struct utmp'. */
#define HAVE_STRUCT_UTMP_UT_HOST 1

/* Define to 1 if `ut_id' is a member of `struct utmp'. */
#define HAVE_STRUCT_UTMP_UT_ID 1

/* Define to 1 if `ut_name' is a member of `struct utmp'. */
#define HAVE_STRUCT_UTMP_UT_NAME 1

/* Define to 1 if `ut_syslen' is a member of `struct utmp'. */
/* #undef HAVE_STRUCT_UTMP_UT_SYSLEN */

/* Define to 1 if `ut_time' is a member of `struct utmp'. */
#define HAVE_STRUCT_UTMP_UT_TIME 1

/* Define to 1 if `ut_tv' is a member of `struct utmp'. */
#define HAVE_STRUCT_UTMP_UT_TV 1

/* Define to 1 if `ut_type' is a member of `struct utmp'. */
#define HAVE_STRUCT_UTMP_UT_TYPE 1

/* Define to 1 if `ut_user' is a member of `struct utmp'. */
#define HAVE_STRUCT_UTMP_UT_USER 1

/* Define to 1 if `ut_xtime' is a member of `struct utmp'. */
#define HAVE_STRUCT_UTMP_UT_XTIME 1

/* Define to 1 if you have the <sys/capability.h> header file. */
/* #undef HAVE_SYS_CAPABILITY_H */

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/random.h> header file. */
#define HAVE_SYS_RANDOM_H 1

/* Define to 1 if you have the <sys/statfs.h> header file. */
#define HAVE_SYS_STATFS_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <tcb.h> header file. */
/* #undef HAVE_TCB_H */

/* Define to 1 if you have the <termio.h> header file. */
#define HAVE_TERMIO_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `updwtmp' function. */
#define HAVE_UPDWTMP 1

/* Define to 1 if you have the `updwtmpx' function. */
#define HAVE_UPDWTMPX 1

/* Define to 1 if you have the <utime.h> header file. */
#define HAVE_UTIME_H 1

/* Define to 1 if `utime(file, NULL)' sets file's timestamp to the present. */
#define HAVE_UTIME_NULL 1

/* Define to 1 if you have the <utmp.h> header file. */
#define HAVE_UTMP_H 1

/* Define to support vendor settings. */
/* #undef HAVE_VENDORDIR */

/* Path for lastlog file. */
#define LASTLOG_FILE "/var/log/lastlog"

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

/* Location of system mail spool directory. */
#define MAIL_SPOOL_DIR "/var/mail"

/* Name of user's mail spool file if stored in user's home directory. */
/* #undef MAIL_SPOOL_FILE */

/* Name of package */
#define PACKAGE "shadow"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "pkg-shadow-devel@lists.alioth.debian.org"

/* Define to the full name of this package. */
#define PACKAGE_NAME "shadow"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "shadow 4.14.0"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "shadow"

/* Define to the home page for this package. */
#define PACKAGE_URL "https://github.com/shadow-maint/shadow"

/* Define to the version of this package. */
#define PACKAGE_VERSION "4.14.0"

/* Path to passwd program. */
#define PASSWD_PROGRAM "/usr/bin/passwd"

/* Define if login should support the -r flag for rlogind. */
/* #undef RLOGIN */

/* Define to the ruserok() "success" return value (0 or 1). */
/* #undef RUSEROK */

/* Define to support the shadow group file. */
#define SHADOWGRP 1

/* PAM conversation to use */
/* #undef SHADOW_PAM_CONVERSATION */

/* The default shell. */
#define SHELL "/bin/bash"

/* The size of `gid_t', as computed by sizeof. */
#define SIZEOF_GID_T 4

/* The size of `uid_t', as computed by sizeof. */
#define SIZEOF_UID_T 4

/* Define to support S/Key logins. */
/* #undef SKEY */

/* Define to support newer BSD S/Key API */
/* #undef SKEY_BSD_STYLE */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to support /etc/suauth su access control. */
#define SU_ACCESS 1

/* Define to allow the bcrypt password encryption algorithm */
/* #undef USE_BCRYPT */

/* Define to support flushing of nscd caches */
#define USE_NSCD 1

/* Define to support Pluggable Authentication Modules */
/* #undef USE_PAM */

/* Define to allow the SHA256 and SHA512 password encryption algorithms */
#define USE_SHA_CRYPT 1

/* Define to support flushing of sssd caches */
#define USE_SSSD 1

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Define to allow the yescrypt password encryption algorithm */
#define USE_YESCRYPT 1

/* Directory for distribution provided configuration files */
/* #undef VENDORDIR */

/* Version number of package */
#define VERSION "4.14.0"

/* Build shadow with ACL support */
/* #undef WITH_ACL */

/* Build shadow with Extended Attributes support */
/* #undef WITH_ATTR */

/* Define if you want to enable Audit messages */
#define WITH_AUDIT 1

/* Build shadow with BtrFS support */
#define WITH_BTRFS 1

/* Build shadow without libbsd support */
#define WITH_LIBBSD 1

/* Build shadow with SELinux support */
/* #undef WITH_SELINUX */

/* Build with su */
#define WITH_SU 1

/* Build shadow with tcb support (incomplete) */
/* #undef WITH_TCB */

/* Enable large inode numbers on Mac OS X 10.5.  */
#ifndef _DARWIN_USE_64_BIT_INODE
# define _DARWIN_USE_64_BIT_INODE 1
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
/* #undef _FILE_OFFSET_BITS */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Path for utmp file. */
#define _UTMP_FILE "none/utmp"

/* Path for wtmp file. */
#define _WTMP_FILE "/var/log/wtmp"

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef gid_t */

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef uid_t */
