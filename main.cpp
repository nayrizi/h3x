#include <cstdio>
#include <cstdlib>
#include <stdint.h>
#include <ctype.h>

#define BYTES_PER_LINE 20

typedef uint8_t byte;

inline void panic(const char* msg);
void        dump(const char *in_file, int bytes_per_line = BYTES_PER_LINE);

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        panic("Usage: h3x [filename] [bytes per line]");
    }
    
    char *filename = argv[1];
    
    if (argv[2] != nullptr)
    {
        auto bytes_per_line = atoi(argv[2]);
        dump(filename, bytes_per_line);
        
        return 0;
    }
    
    dump(filename);
    
    return 0;
    
}

inline void panic(const char* msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(EXIT_FAILURE);
}

void dump(const char *in_file, int bytes_per_line)
{
    FILE *in = fopen(in_file, "rb");
    
    if (in == nullptr)
    {
        fprintf(stderr, "Coulnd't open %s\n", in_file);
        exit(EXIT_FAILURE);
    }
    
    byte b[bytes_per_line];
    uint64_t i = 0;
    
    while(!feof(in))
    {
        fread(&b, sizeof(byte) * bytes_per_line , 1, in);
        printf("%010x: ", i);
        
        for (auto j=0; j<bytes_per_line; j++)
        {
            printf("%2x ", b[j]);
        }
        
        printf("\t");
        for (auto j=0; j<bytes_per_line; j++)
        {
            if (!isalpha(b[j]))
            {
                printf(".");
            }
            else
            {
                printf("%c", b[j]);
            }
        }
        printf("\n");
        i++;
    }
    
    fclose(in);
}