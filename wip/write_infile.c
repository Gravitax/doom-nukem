#include <stdio.h>
#include "../libft/libft.h"

/*
r   : Lecture seule. Le fichier doit avoir été créé au préalable.
w   : Ecriture seule. Si le fichier n'existe pas, il sera créé.
a   : Ecriture en partant de la fin du fichier. Si le fichier n'existe pas, il sera créé.
r+  : Lecture et écriture. Le fichier doit avoir été créé au préalable.
w+  : Lecture et écriture, avec suppression du contenu au préalable. Si le fichier n'existe pas, il sera créé.
a+  : Ajout en lecture / écriture à part de la fin. Si le fichier n'existe pas, il sera créé.
+b  : Ecriture en binaire.
*/

int         write_infile(char *f_name, char *str)
{
    FILE*   file;
 
    file = fopen(f_name, "w");
    if (file)
    {
        fprintf(file, "%s", str);
        fclose(file);
        return (1);
    }
    return (0);
}

int         main(int ac, char **av)
{
    if (write_infile("test.txt", "TEST\n") == 0)
        puts("error writing in the file");
    return (0);
}
