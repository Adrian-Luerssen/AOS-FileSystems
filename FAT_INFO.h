#ifndef AOS_FILESYSTEMS_FAT_INFO_H
#define AOS_FILESYSTEMS_FAT_INFO_H

#define BS_JMPBOOT_OFFSET 0
#define BS_JMPBOOT_SIZE 3
#define BS_OEMNAME_OFFSET 3
#define BS_OEMNAME_SIZE 8
#define BPB_BYTSPERSEC_OFFSET 11
#define BPB_BYTSPERSEC_SIZE 2
#define BPB_SECPERCLUS_OFFSET 13
#define BPB_SECPERCLUS_SIZE 1
#define BPB_RSVDSECCNT_OFFSET 14
#define BPB_RSVDSECCNT_SIZE 2
#define BPB_NUMFATS_OFFSET 16
#define BPB_NUMFATS_SIZE 1
#define BPB_ROOTENTCNT_OFFSET 17
#define BPB_ROOTENTCNT_SIZE 2
#define BPB_TOTSEC16_OFFSET 19
#define BPB_TOTSEC16_SIZE 2
#define BPB_MEDIA_OFFSET 21
#define BPB_MEDIA_SIZE 1
#define BPB_FATSZ16_OFFSET 22
#define BPB_FATSZ16_SIZE 2
#define BPB_SECPERTRK_OFFSET 24
#define BPB_SECPERTRK_SIZE 2
#define BPB_NUMHEADS_OFFSET 26
#define BPB_NUMHEADS_SIZE 2
#define BPB_HIDDSEC_OFFSET 28
#define BPB_HIDDSEC_SIZE 4
#define BPB_TOTSEC32_OFFSET 32
#define BPB_TOTSEC32_SIZE 4

#define BS_DRVNUM_OFFSET 36
#define BS_DRVNUM_SIZE 1
#define BS_RESERVED1_OFFSET 37
#define BS_RESERVED1_SIZE 1
#define BS_BOOTSIG_OFFSET 38
#define BS_BOOTSIG_SIZE 1
#define BS_VOLID_OFFSET 39
#define BS_VOLID_SIZE 4
#define BS_VOLLAB_OFFSET 43
#define BS_VOLLAB_SIZE 11
#define BS_FILSYSTYPE_OFFSET 54
#define BS_FILSYSTYPE_SIZE 8

#define FAT32_BPB_FATSZ32_OFFSET 36
#define FAT32_BPB_FATSZ32_SIZE 4
#define FAT32_BPB_EXTFLAGS_OFFSET 40
#define FAT32_BPB_EXTFLAGS_SIZE 2
#define FAT32_BPB_FSVER_OFFSET 42
#define FAT32_BPB_FSVER_SIZE 2
#define FAT32_BPB_ROOTCLUS_OFFSET 44
#define FAT32_BPB_ROOTCLUS_SIZE 4
#define FAT32_BPB_FSINFO_OFFSET 48
#define FAT32_BPB_FSINFO_SIZE 2
#define FAT32_BPB_BKBOOTSEC_OFFSET 50
#define FAT32_BPB_BKBOOTSEC_SIZE 2
#define FAT32_BPB_RESERVED_OFFSET 52
#define FAT32_BPB_RESERVED_SIZE 12
#define FAT32_BS_DRVNUM_OFFSET 64
#define FAT32_BS_DRVNUM_SIZE 1
#define FAT32_BS_RESERVED1_OFFSET 65
#define FAT32_BS_RESERVED1_SIZE 1
#define FAT32_BS_BOOTSIG_OFFSET 66
#define FAT32_BS_BOOTSIG_SIZE 1
#define FAT32_BS_VOLID_OFFSET 67
#define FAT32_BS_VOLID_SIZE 4
#define FAT32_BS_VOLLAB_OFFSET 71
#define FAT32_BS_VOLLAB_SIZE 11
#define FAT32_BS_FILSYSTYPE_OFFSET 82
#define FAT32_BS_FILSYSTYPE_SIZE 8


#define FAT12_TYPE_STRING "FAT12   "
#define FAT16_TYPE_STRING "FAT16   "
#define FAT_TYPE_STRING   "FAT     "
#define FAT32_TYPE_STRING "FAT32   "


#define FAT_DIR_NAME_OFFSET 0
#define FAT_DIR_NAME_SIZE 11
#define FAT_DIR_ATTR_OFFSET 11
#define FAT_DIR_ATTR_SIZE 1
#define FAT_DIR_NTRES_OFFSET 12
#define FAT_DIR_NTRES_SIZE 1
#define FAT_DIR_CRTTIME_OFFSET 14
#define FAT_DIR_CRTTIME_SIZE 2
#define FAT_DIR_CRTDATE_OFFSET 16
#define FAT_DIR_CRTDATE_SIZE 2
#define FAT_DIR_LSTACC_DATE_OFFSET 18
#define FAT_DIR_LSTACC_DATE_SIZE 2
#define FAT_DIR_FSTCLUSHI_OFFSET 20
#define FAT_DIR_FSTCLUSHI_SIZE 2
#define FAT_DIR_WRTTIME_OFFSET 22
#define FAT_DIR_WRTTIME_SIZE 2
#define FAT_DIR_WRTDATE_OFFSET 24
#define FAT_DIR_WRTDATE_SIZE 2
#define FAT_DIR_FSTCLUSLO_OFFSET 26
#define FAT_DIR_FSTCLUSLO_SIZE 2
#define FAT_DIR_FILESIZE_OFFSET 28
#define FAT_DIR_FILESIZE_SIZE 4


#endif