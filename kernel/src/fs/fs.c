#include "common.h"
#include <string.h>
typedef struct {
	char *name;
	uint32_t size;
	uint32_t disk_offset;
} file_info;

enum {SEEK_SET, SEEK_CUR, SEEK_END};

/* This is the information about all files in disk. */
static const file_info file_table[] = {
	{"1.rpg", 188864, 1048576}, {"2.rpg", 188864, 1237440},
	{"3.rpg", 188864, 1426304}, {"4.rpg", 188864, 1615168},
	{"5.rpg", 188864, 1804032}, {"abc.mkf", 1022564, 1992896},
	{"ball.mkf", 134704, 3015460}, {"data.mkf", 66418, 3150164},
	{"desc.dat", 16027, 3216582}, {"fbp.mkf", 1128064, 3232609},
	{"fire.mkf", 834728, 4360673}, {"f.mkf", 186966, 5195401},
	{"gop.mkf", 11530322, 5382367}, {"map.mkf", 1496578, 16912689},
	{"mgo.mkf", 1577442, 18409267}, {"m.msg", 188232, 19986709},
	{"mus.mkf", 331284, 20174941}, {"pat.mkf", 8488, 20506225},
	{"rgm.mkf", 453202, 20514713}, {"rng.mkf", 4546074, 20967915},
	{"sss.mkf", 557004, 25513989}, {"voc.mkf", 1997044, 26070993},
	{"wor16.asc", 5374, 28068037}, {"wor16.fon", 82306, 28073411},
	{"word.dat", 5650, 28155717},
};

#define NR_FILES (sizeof(file_table) / sizeof(file_table[0]))
#define FILE_OFF 3
void ide_read(uint8_t *, uint32_t, uint32_t);
void ide_write(uint8_t *, uint32_t, uint32_t);

/* TODO: implement a simplified file system here. */
struct 
{
    	bool opened;
    	uint32_t offset;
} f_state[NR_FILES + 3];

int fs_open(const char *pathname, int flags) 
{
	int i = 0;
    	for (i = 0; i < NR_FILES; i++) 
    	{
        		if (strcmp(file_table[i].name, pathname) == 0) 
        		{
            		int fd = i + FILE_OFF;
            		f_state[fd].opened = true;
            		f_state[fd].offset = 0;
            		return fd;
        		}
    	}
    	panic("File Error!");
    	return -1;
}

int fs_read(int fd, void *buf, size_t len) 
{
    	if (fd < FILE_OFF) return -1;
    	assert(fd < NR_FILES + FILE_OFF);
    	assert(f_state[fd].opened);
    	int max_len = file_table[fd - FILE_OFF].size - f_state[fd].offset;
   	assert(max_len >= 0);
    	if (max_len < len) len = max_len;
    	ide_read(buf, file_table[fd - FILE_OFF].disk_offset + f_state[fd].offset, len);
    	f_state[fd].offset += len;
    	return len;
}

int fs_write(int fd, void *buf, size_t len) 
{
	if (fd < FILE_OFF) return -1;
    	assert(fd < NR_FILES + FILE_OFF);
    	assert(f_state[fd].opened);
    	int max_len = file_table[fd - FILE_OFF].size - f_state[fd].offset;
   	assert(max_len >= 0);
    	if (max_len < len) len = max_len;
    	ide_write((uint8_t *)buf, file_table[fd - FILE_OFF].disk_offset + f_state[fd].offset, len);
    	f_state[fd].offset += len;
    	return len;
}

off_t fs_lseek(int fd, off_t offset, int whence) 
{
 	 if (fd < FILE_OFF) return -1;
    	assert(fd < NR_FILES + FILE_OFF);
    	assert(f_state[fd].opened);
   	 switch (whence) 
   	 {
        		case SEEK_SET: f_state[fd].offset = 0; break;
        		case SEEK_CUR: break;
        		case SEEK_END: f_state[fd].offset = file_table[fd - FILE_OFF].size; break;
        		default: assert(0);
    	}
    	f_state[fd].offset += offset;
    	assert(f_state[fd].offset >= 0);
    	assert(f_state[fd].offset <= file_table[fd - FILE_OFF].size);
    	return f_state[fd].offset;
}

int fs_close(int fd) 
{
    	assert(f_state[fd].opened);
    	f_state[fd].opened = false;
    	return 0;
}

    

