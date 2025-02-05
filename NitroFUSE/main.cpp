/**
 * @file		main.cpp
 * @author		Name <email>
 * @date 		2-2025
 * @version		alpha
 * @copyright
 * This file is part of NitroFUSE, a FUSE implementation for DS ROMs.
 * Copyright (C) 2025 {NAME}
 * @par
 * This program is free/libre software and can be distributed under the terms of the GNU GPLv3.
 * See LICENSE in the project root directory for the full license text.
 * @brief
 * This is the entry point of the project.
 * @remark
 * The C++ standard used in NitroFUSE is C++20.
 */

/**
 * @def
 * @brief
 * Enable asserts by commenting out the @p #undef statement.
 */
#define NODEBUG 1
#undef NODEBUG

/**
 * @def FUSE_USE_VERSION
 * @brief
 * Specifying this is necessary before including @p <fuse.h> to use the current API.
 * @details
 * If not specified, @c libfuse sets an older value by default, forcing use of the old API.
 */
#define FUSE_USE_VERSION 35
#include <fuse3/fuse.h>

//#include "./cmdline.h"
#include "./process_rom.h"

#include <fstream>
#include <string>

/**
 * @def _WIN32
 * @brief
 * Check whether platform is 32- or 64-bit Windows to enable Windows compatibility through WinFSP.
 * @details
 * The @p NOMINMAX definition prevents collision in namespace @p std of min/max functions.
 */
#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
// Todo: include <winfsp/winfsp.h>
#endif

int main() {
	// Implement cmdline.cpp to get fileName from CLI instead of hardcoding it
	const std::string fileName = "../aj.nds";
	int result = processRom(fileName);


	return 0;
}


	// fuse_context struct is a pointer to a fuse struct, then uid, gid, pid, private_data, and mode_t umask
	// fuse_main: macro for fuse_main_real() - takes argc, argv (without element 0), fuse_operations struct, then private_data
	// fuse_main is all that absolutely needs to be called here in main()
	// private_data is set by the return value of init(), which takes a fuse_config struct
	// choice of fuse_loop() vs. fuse_loop_mt()
	// fuse_opt_parse() from the low-level API is an option

	// Members of fuse_operations struct, which directly return -errno:
	/* int (*getattr) (const char *, struct stat *, struct fuse_file_info *fi);
	int (*readlink) (const char *, char *, size_t);
	int (*mknod) (const char *, mode_t, dev_t);
	int (*mkdir) (const char *, mode_t);
	int (*unlink) (const char *);
	int (*rmdir) (const char *);
	int (*symlink) (const char *, const char *);
	int (*rename) (const char *, const char *, unsigned int flags);
	int (*link) (const char *, const char *);
	int (*chmod) (const char *, mode_t, struct fuse_file_info *fi);
	int (*chown) (const char *, uid_t, gid_t, struct fuse_file_info *fi);
	int (*truncate) (const char *, off_t, struct fuse_file_info *fi);
	int (*open) (const char *, struct fuse_file_info *);
	int (*read) (const char *, char *, size_t, off_t,
		struct fuse_file_info *);
	int (*write) (const char *, const char *, size_t, off_t,
		struct fuse_file_info *);
	int (*statfs) (const char *, struct statvfs *);
	int (*flush) (const char *, struct fuse_file_info *);
	int (*release) (const char *, struct fuse_file_info *);
	int (*fsync) (const char *, int, struct fuse_file_info *);
	int (*setxattr) (const char *, const char *, const char *, size_t, int);
	int (*getxattr) (const char *, const char *, char *, size_t);
	int (*listxattr) (const char *, char *, size_t);
	int (*removexattr) (const char *, const char *);
	int (*opendir) (const char *, struct fuse_file_info *);
	int (*readdir) (const char *, void *, fuse_fill_dir_t, off_t,
		struct fuse_file_info *, enum fuse_readdir_flags);
	int (*releasedir) (const char *, struct fuse_file_info *);
	int (*fsyncdir) (const char *, int, struct fuse_file_info *);
	void *(*init) (struct fuse_conn_info *conn,
		struct fuse_config *cfg);
	void (*destroy) (void *private_data);
	int (*access) (const char *, int);
	int (*create) (const char *, mode_t, struct fuse_file_info *);
	int (*lock) (const char *, struct fuse_file_info *, int cmd,
		struct flock *);
	int (*utimens) (const char *, const struct timespec tv[2],
		struct fuse_file_info *fi);
	int (*bmap) (const char *, size_t blocksize, uint64_t *idx);
	int (*ioctl) (const char *, unsigned int cmd, void *arg,
		struct fuse_file_info *, unsigned int flags, void *data);
	int (*poll) (const char *, struct fuse_file_info *,
		struct fuse_pollhandle *ph, unsigned *reventsp);
	int (*write_buf) (const char *, struct fuse_bufvec *buf, off_t off,
		struct fuse_file_info *);
	int (*read_buf) (const char *, struct fuse_bufvec **bufp,
		size_t size, off_t off, struct fuse_file_info *);
	int (*flock) (const char *, struct fuse_file_info *, int op);
	int (*fallocate) (const char *, int, off_t, off_t,
		struct fuse_file_info *);
	ssize_t (*copy_file_range) (const char *path_in,
		struct fuse_file_info *fi_in,
		off_t offset_in, const char *path_out,
		struct fuse_file_info *fi_out,
		off_t offset_out, size_t size, int flags);
	off_t (*lseek) (const char *, off_t off, int whence, struct fuse_file_info *);

	// Members of fuse_config, initialized by arguments to fuse_new():
	int set_gid = 0; // No need to overwrite st_gid in every file with the value of 'gid'
	unsigned int gid;
	int set_uid = 0; // No need to overwrite st_uid in every file with the value of 'uid'
	unsigned int uid;
	int set_mode = 0; // No need to overwrite 'umask' value in st_mode of each file
	unsigned int umask;
	double entry_timeout = 60; // Number of seconds for which to cache name lookups
	double negative_timeout = 3; // Cache a lookup result of ENOENT for three seconds
	double attr_timeout = 10; // Number of seconds for file attributes, e.g., from get_attr(), to be cached
	int intr = 1; // Allow filesystem requests to be interrupted
	int intr_signal = 10; // USR1, the default signal
	int remember = 5; // Kernel will cache inodes for five seconds after they are released
	int hard_remove = 0; // When an open file is deleted, let FUSE hold onto it until close
	int use_ino = 1; // "Honor the st_ino field in the functions getattr() and fill_dir()"; FS-wide unique inodes preferred
	int readdir_ino = 1; // Ignored, as use_ino as set
	int direct_io = 1; // Disables kernel page cache, allows direct return values from read/write calls
	int kernel_cache = 0; // Enables flushing cache of file contents on every call to open()
	int auto_cache = 1; // A smarter version of kernel_cache, keeps cache on open() unless timestamp/file size has changed
	int no_rofd_flush = 0; // Tells FUSE to wait for all pending writes before flushing even a read-only file
	int ac_attr_timeout_set = 1; // (I think, may have to verify) enables timestamp/size caching for auto_cache
	double ac_attr_timeout = 30; // Number of seconds for which to cache timestamp/size for auto_cache
	int nullpath_ok = 0; // Ensures that all FUSE operations receive path information

	// The following options are for FUSE-internal use, and so they should not be changed
	int show_help;
	char *modules;
	int debug;
	*/
