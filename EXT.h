//
// Created by adril on 13/04/2023.
//

#ifndef AOS_FILESYSTEMS_EXT_H
#define AOS_FILESYSTEMS_EXT_H
#include <stdbool.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// *********************************** EXT2 Superblock *********************************** //
#define EXT2_S_INODES_COUNT_OFFSET 0
#define EXT2_S_INODES_COUNT_SIZE 4
#define EXT2_S_BLOCKS_COUNT_OFFSET 4
#define EXT2_S_BLOCKS_COUNT_SIZE 4
#define EXT2_S_R_BLOCKS_COUNT_OFFSET 8
#define EXT2_S_R_BLOCKS_COUNT_SIZE 4
#define EXT2_S_FREE_BLOCKS_COUNT_OFFSET 12
#define EXT2_S_FREE_BLOCKS_COUNT_SIZE 4
#define EXT2_S_FREE_INODES_COUNT_OFFSET 16
#define EXT2_S_FREE_INODES_COUNT_SIZE 4
#define EXT2_S_FIRST_DATA_BLOCK_OFFSET 20
#define EXT2_S_FIRST_DATA_BLOCK_SIZE 4
#define EXT2_S_LOG_BLOCK_SIZE_OFFSET 24
#define EXT2_S_LOG_BLOCK_SIZE_SIZE 4
#define EXT2_S_LOG_FRAG_SIZE_OFFSET 28
#define EXT2_S_LOG_FRAG_SIZE_SIZE 4
#define EXT2_S_BLOCKS_PER_GROUP_OFFSET 32
#define EXT2_S_BLOCKS_PER_GROUP_SIZE 4
#define EXT2_S_FRAGS_PER_GROUP_OFFSET 36
#define EXT2_S_FRAGS_PER_GROUP_SIZE 4
#define EXT2_S_INODES_PER_GROUP_OFFSET 40
#define EXT2_S_INODES_PER_GROUP_SIZE 4
#define EXT2_S_MTIME_OFFSET 44
#define EXT2_S_MTIME_SIZE 4
#define EXT2_S_WTIME_OFFSET 48
#define EXT2_S_WTIME_SIZE 4
#define EXT2_S_MNT_COUNT_OFFSET 52
#define EXT2_S_MNT_COUNT_SIZE 2
#define EXT2_S_MAX_MNT_COUNT_OFFSET 54
#define EXT2_S_MAX_MNT_COUNT_SIZE 2
#define EXT2_S_MAGIC_OFFSET 56
#define EXT2_S_MAGIC_SIZE 2
#define EXT2_S_STATE_OFFSET 58
#define EXT2_S_STATE_SIZE 2
#define EXT2_S_ERRORS_OFFSET 60
#define EXT2_S_ERRORS_SIZE 2
#define EXT2_S_MINOR_REV_LEVEL_OFFSET 62
#define EXT2_S_MINOR_REV_LEVEL_SIZE 2
#define EXT2_S_LASTCHECK_OFFSET 64
#define EXT2_S_LASTCHECK_SIZE 4
#define EXT2_S_CHECKINTERVAL_OFFSET 68
#define EXT2_S_CHECKINTERVAL_SIZE 4
#define EXT2_S_CREATOR_OS_OFFSET 72
#define EXT2_S_CREATOR_OS_SIZE 4
#define EXT2_S_REV_LEVEL_OFFSET 76
#define EXT2_S_REV_LEVEL_SIZE 4
#define EXT2_S_DEF_RESUID_OFFSET 80
#define EXT2_S_DEF_RESUID_SIZE 2
#define EXT2_S_DEF_RESGID_OFFSET 82
#define EXT2_S_DEF_RESGID_SIZE 2

// EXT2_DYNAMIC_REV Specific
#define EXT2_S_FIRST_INO_OFFSET 84
#define EXT2_S_FIRST_INO_SIZE 4
#define EXT2_S_INODE_SIZE_OFFSET 88
#define EXT2_S_INODE_SIZE_SIZE 2
#define EXT2_S_BLOCK_GROUP_NR_OFFSET 90
#define EXT2_S_BLOCK_GROUP_NR_SIZE 2
#define EXT2_S_FEATURE_COMPAT_OFFSET 92
#define EXT2_S_FEATURE_COMPAT_SIZE 4
#define EXT2_S_FEATURE_INCOMPAT_OFFSET 96
#define EXT2_S_FEATURE_INCOMPAT_SIZE 4
#define EXT2_S_FEATURE_RO_COMPAT_OFFSET 100
#define EXT2_S_FEATURE_RO_COMPAT_SIZE 4
#define EXT2_S_UUID_OFFSET 104
#define EXT2_S_UUID_SIZE 16
#define EXT2_S_VOLUME_NAME_OFFSET 120
#define EXT2_S_VOLUME_NAME_SIZE 16
#define EXT2_S_LAST_MOUNTED_OFFSET 136
#define EXT2_S_LAST_MOUNTED_SIZE 64
#define EXT2_S_ALGO_BITMAP_OFFSET 200
#define EXT2_S_ALGO_BITMAP_SIZE 4

// Performance Hints
#define EXT2_S_PREALLOC_BLOCKS_OFFSET 204
#define EXT2_S_PREALLOC_BLOCKS_SIZE 1
#define EXT2_S_PREALLOC_DIR_BLOCKS_OFFSET 205
#define EXT2_S_PREALLOC_DIR_BLOCKS_SIZE 1

// Journaling Support
#define EXT2_S_JOURNAL_UUID_OFFSET 208
#define EXT2_S_JOURNAL_UUID_SIZE 16
#define EXT2_S_JOURNAL_INUM_OFFSET 224
#define EXT2_S_JOURNAL_INUM_SIZE 4
#define EXT2_S_JOURNAL_DEV_OFFSET 228
#define EXT2_S_JOURNAL_DEV_SIZE 4
#define EXT2_S_LAST_ORPHAN_OFFSET 232
#define EXT2_S_LAST_ORPHAN_SIZE 4

// Directory Indexing Support
#define EXT2_S_HASH_SEED_OFFSET 236
#define EXT2_S_HASH_SEED_SIZE 16
#define EXT2_S_DEF_HASH_VERSION_OFFSET 252
#define EXT2_S_DEF_HASH_VERSION_SIZE 1

// Other options
#define EXT2_S_DEFAULT_MOUNT_OPTIONS_OFFSET 256
#define EXT2_S_DEFAULT_MOUNT_OPTIONS_SIZE 4
#define EXT2_S_FIRST_META_BG_OFFSET 260
#define EXT2_S_FIRST_META_BG_SIZE 4

#define EXT2_SUPER_BLOCK_1_OFFSET 1024
#define EXT2_SUPER_BLOCK_1_SIZE 1024

#define EXT2_BLOCK_GROUP_DESCRIPTOR_OFFSET 2048

#define EXT2_SUPER_MAGIC  0xEF53

bool isExt(int fd);
#endif //AOS_FILESYSTEMS_EXT_H
