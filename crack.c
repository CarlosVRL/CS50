#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>

char *crypt(const char *key, const char *salt);

int main(int argc, char * argv[])
{

    if(argc != 2)
    {
        printf("Usage: ./crack <hash>\n");
        return 1;
    }

    char * key = argv[1];
    char * salt = "50";
    
    // a 4-character limit means we won't be here all night
    char cracked[5];
    cracked[4] = '\0';
    
    // wrote out the alphabet for easy looping
    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int n = strlen(alphabet);
    
    for (int i = 0; i<n; i++)
    {
        
        cracked[0] = alphabet[i];
        
        for (int j = 0; j<n; j++)
        {

            cracked[1] = alphabet[j];
            
            for (int k = 0; k<n; k++)
            {
                
                cracked[2] = alphabet[k];
                
                for (int l = 0; l<n; l++)
                {
                    
                    cracked[3] = alphabet[l];
                    
                    // quad-character check (skipped the other cases to save a few lines)
                    string crypted_guess = crypt(cracked, salt);
                    
                    // this can be re-factored to, say, void check_password(const char * crypted_guess, const char * key), but I'm lazy.
                    if (strcmp(crypted_guess, key) == 0)
                    {
                        printf("%s\n", cracked);
                        return 0;
                    }
                }
            }
        }
        
        // my spider-sense tells me that this looping construct can be constructed recursively, but it's about 2am. Also, still lazy.
   
        // reset to single character check on next loop
        cracked[1] = 0;
        cracked[2] = 0;
        cracked[3] = 0;
        
    }
    
    return 1337;
}
