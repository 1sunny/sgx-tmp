/*
 * SPDX-FileCopyrightText: 1990 - 1994, Julianne Frances Haugh
 * SPDX-FileCopyrightText: 1996 - 2000, Marek Michałkiewicz
 * SPDX-FileCopyrightText: 2001       , Michał Moskal
 * SPDX-FileCopyrightText: 2005       , Tomasz Kłoczko
 * SPDX-FileCopyrightText: 2007 - 2013, Nicolas François
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "config.h"

#ifdef SHADOWGRP

#ident "$Id$"

#include "alloc.h"
#include "prototypes.h"
// #include "defines.h"
#include "commonio.h"
// #include "getdef.h"
#include "memzero.h"
#include "sgroupio.h"

/*@null@*/ /*@only@*/struct sgrp *__sgr_dup (const struct sgrp *sgent)
{
	struct sgrp *sg;
	int i;

	sg = CALLOC (1, struct sgrp);
	if (NULL == sg) {
		return NULL;
	}
	/* Do the same as the other _dup function, even if we know the
	 * structure. */
	/*@-mustfreeonly@*/
	sg->sg_name = strdup (sgent->sg_name);
	/*@=mustfreeonly@*/
	if (NULL == sg->sg_name) {
		free (sg);
		return NULL;
	}
	/*@-mustfreeonly@*/
	sg->sg_passwd = strdup (sgent->sg_passwd);
	/*@=mustfreeonly@*/
	if (NULL == sg->sg_passwd) {
		free (sg->sg_name);
		free (sg);
		return NULL;
	}

	for (i = 0; NULL != sgent->sg_adm[i]; i++);
	/*@-mustfreeonly@*/
	sg->sg_adm = MALLOC(i + 1, char *);
	/*@=mustfreeonly@*/
	if (NULL == sg->sg_adm) {
		free (sg->sg_passwd);
		free (sg->sg_name);
		free (sg);
		return NULL;
	}
	for (i = 0; NULL != sgent->sg_adm[i]; i++) {
		sg->sg_adm[i] = strdup (sgent->sg_adm[i]);
		if (NULL == sg->sg_adm[i]) {
			for (i = 0; NULL != sg->sg_adm[i]; i++) {
				free (sg->sg_adm[i]);
			}
			free (sg->sg_adm);
			free (sg->sg_passwd);
			free (sg->sg_name);
			free (sg);
			return NULL;
		}
	}
	sg->sg_adm[i] = NULL;

	for (i = 0; NULL != sgent->sg_mem[i]; i++);
	/*@-mustfreeonly@*/
	sg->sg_mem = MALLOC(i + 1, char *);
	/*@=mustfreeonly@*/
	if (NULL == sg->sg_mem) {
		for (i = 0; NULL != sg->sg_adm[i]; i++) {
			free (sg->sg_adm[i]);
		}
		free (sg->sg_adm);
		free (sg->sg_passwd);
		free (sg->sg_name);
		free (sg);
		return NULL;
	}
	for (i = 0; NULL != sgent->sg_mem[i]; i++) {
		sg->sg_mem[i] = strdup (sgent->sg_mem[i]);
		if (NULL == sg->sg_mem[i]) {
			for (i = 0; NULL != sg->sg_mem[i]; i++) {
				free (sg->sg_mem[i]);
			}
			free (sg->sg_mem);
			for (i = 0; NULL != sg->sg_adm[i]; i++) {
				free (sg->sg_adm[i]);
			}
			free (sg->sg_adm);
			free (sg->sg_passwd);
			free (sg->sg_name);
			free (sg);
			return NULL;
		}
	}
	sg->sg_mem[i] = NULL;

	return sg;
}

static /*@null@*/ /*@only@*/void *gshadow_dup (const void *ent)
{
	const struct sgrp *sg = ent;

	return __sgr_dup (sg);
}

static void gshadow_free (/*@out@*/ /*@only@*/void *ent)
{
	struct sgrp *sg = ent;

	sgr_free (sg);
}

void sgr_free (/*@out@*/ /*@only@*/struct sgrp *sgent)
{
	size_t i;
	free (sgent->sg_name);
	if (NULL != sgent->sg_passwd) {
		strzero (sgent->sg_passwd);
		free (sgent->sg_passwd);
	}
	for (i = 0; NULL != sgent->sg_adm[i]; i++) {
		free (sgent->sg_adm[i]);
	}
	free (sgent->sg_adm);
	for (i = 0; NULL != sgent->sg_mem[i]; i++) {
		free (sgent->sg_mem[i]);
	}
	free (sgent->sg_mem);
	free (sgent);
}

static const char *gshadow_getname (const void *ent)
{
	const struct sgrp *gr = ent;

	return gr->sg_name;
}

static void *gshadow_parse (const char *line)
{
	return sgetsgent (line);
}

int putsgent (const struct sgrp *sgrp, FILE * fp)
{
	char *buf, *cp;
	int i;
	size_t size;

	if ((NULL == fp) || (NULL == sgrp)) {
		return -1;
	}

	/* calculate the required buffer size */
	size_t name_len = strlen(sgrp->sg_name);
	size_t passwd_len = strlen(sgrp->sg_passwd);
	size = name_len + passwd_len + 10;
	for (i = 0; (NULL != sgrp->sg_adm) && (NULL != sgrp->sg_adm[i]); i++) {
		size += strlen (sgrp->sg_adm[i]) + 1;
	}
	for (i = 0; (NULL != sgrp->sg_mem) && (NULL != sgrp->sg_mem[i]); i++) {
		size += strlen (sgrp->sg_mem[i]) + 1;
	}

	buf = MALLOC(size, char);
	if (NULL == buf) {
		return -1;
	}
	cp = buf;

	/*
	 * Copy the group name and passwd.
	 */

	strncpy (cp, sgrp->sg_name, name_len);
	cp += name_len;
	*cp++ = ':';

	strncpy (cp, sgrp->sg_passwd, passwd_len);
	cp += passwd_len;
	*cp++ = ':';

	/*
	 * Copy the administrators, separating each from the other
	 * with a ",".
	 */

	for (i = 0; NULL != sgrp->sg_adm[i]; i++) {
		if (i > 0) {
			*cp++ = ',';
		}

		size_t len = strlen(sgrp->sg_adm[i]);
		strncpy (cp, sgrp->sg_adm[i], len);
		cp += len;
	}
	*cp = ':';
	cp++;

	/*
	 * Now do likewise with the group members.
	 */

	for (i = 0; NULL != sgrp->sg_mem[i]; i++) {
		if (i > 0) {
			*cp = ',';
			cp++;
		}

		size_t len = strlen(sgrp->sg_mem[i]);
		strncpy (cp, sgrp->sg_mem[i], len);
		cp += len;
	}
	*cp = '\n';
	cp++;
	*cp = '\0';

	/*
	 * Output using the function which understands the line
	 * continuation conventions.
	 */

	if (fputsx (buf, 1) == EOF) {
		free (buf);
		return -1;
	}

	free (buf);
	return 0;
}

static int gshadow_put (const void *ent, FILE * file)
{
	const struct sgrp *sg = ent;

	if (   (NULL == sg)
	    || (valid_field (sg->sg_name, ":\n") == -1)
	    || (valid_field (sg->sg_passwd, ":\n") == -1)) {
		return -1;
	}

	/* FIXME: fail also if sg->sg_adm == NULL ?*/
	if (NULL != sg->sg_adm) {
		size_t i;
		for (i = 0; NULL != sg->sg_adm[i]; i++) {
			if (valid_field (sg->sg_adm[i], ",:\n") == -1) {
				return -1;
			}
		}
	}

	/* FIXME: fail also if sg->sg_mem == NULL ?*/
	if (NULL != sg->sg_mem) {
		size_t i;
		for (i = 0; NULL != sg->sg_mem[i]; i++) {
			if (valid_field (sg->sg_mem[i], ",:\n") == -1) {
				return -1;
			}
		}
	}

	return (putsgent (sg, file) == -1) ? -1 : 0;
}

static struct commonio_ops gshadow_ops = {
	gshadow_dup,
	gshadow_free,
	gshadow_getname,
	gshadow_parse,
	gshadow_put,
	fgetsx,
	fputsx,
	NULL,			/* open_hook */
	NULL			/* close_hook */
};

static struct commonio_db gshadow_db = {
	SGROUP_FILE,		/* filename */
	&gshadow_ops,		/* ops */
	NULL,			/* fp */
#ifdef WITH_SELINUX
	NULL,			/* scontext */
#endif
	0400,                   /* st_mode */
	0,                      /* st_uid */
	0,                      /* st_gid */
	NULL,			/* head */
	NULL,			/* tail */
	NULL,			/* cursor */
	false,			/* changed */
	false,			/* isopen */
	false,			/* locked */
	false,			/* readonly */
	false			/* setname */
};

int sgr_setdbname (const char *filename)
{
	return commonio_setname (&gshadow_db, filename);
}

/*@observer@*/const char *sgr_dbname (void)
{
	return gshadow_db.filename;
}

// bool sgr_file_present (void)
// {
// 	if (getdef_bool ("FORCE_SHADOW"))
// 		return true;
// 	return commonio_present (&gshadow_db);
// }

// int sgr_lock (void)
// {
// 	return commonio_lock (&gshadow_db);
// }
char *scontent = "root:$6$SrqkbhKcyYfhUFU0$YoEgbHrr8g5UxtlbiBhv05Zgf5J161PET3khTggIIqjruWCZ2vo.HKE6nYBoc4o.0lkXRVXZT5OSw3JhZL68k1::\n"
								"daemon:*::\n";

void set_sgr_content(char* s) {
  scontent = xstrdup(s);
}

int sgr_open (int mode)
{
	return commonio_open (&gshadow_db, mode, scontent);
}

/*@observer@*/ /*@null@*/void sgr_locate (const char *name, void* tmp)
{
	commonio_locate (&gshadow_db, name, tmp, 2);
}

int sgr_update (const struct sgrp *sg)
{
	return commonio_update (&gshadow_db, sg);
}

int sgr_remove (const char *name)
{
	return commonio_remove (&gshadow_db, name);
}

int sgr_rewind (void)
{
	return commonio_rewind (&gshadow_db);
}

/*@null@*/const struct sgrp *sgr_next (void)
{
	return commonio_next (&gshadow_db);
}

int sgr_close (void)
{
	gshadow_db.fp = fopen("sgroup.txt", "w");
	int i = commonio_close(&gshadow_db, 1);
	fclose(gshadow_db.fp);
	return i;
}

// int sgr_unlock (void)
// {
// 	return commonio_unlock (&gshadow_db);
// }

void __sgr_set_changed (void)
{
	gshadow_db.changed = true;
}

/*@dependent@*/ /*@null@*/struct commonio_entry *__sgr_get_head (void)
{
	return gshadow_db.head;
}

void __sgr_del_entry (const struct commonio_entry *ent)
{
	commonio_del_entry (&gshadow_db, ent);
}

/* Sort with respect to group ordering. */
int sgr_sort ()
{
	return commonio_sort_wrt (&gshadow_db, __gr_get_db ());
}
#else
extern int ISO_C_forbids_an_empty_translation_unit;
#endif
