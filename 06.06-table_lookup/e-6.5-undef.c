/* Write a function undef that will remove a name and definition from the table
   maintained by lookup and install .*/
void undef(char *s)
{
    struct nlist *np1, *np2;
    unsigned hashval = hash(s);

    for (np1 = hashtab[hashval], np2 = NULL; 
         np1 != NULL;
         np2 = np1, np1 = np1->next) 
        if (strcmp(s, np1->name) == 0) {
            /* found a match */
            free(np1->name);
            free(np1->defn);
            if (np2 == NULL) 
                /* at the beginning? */
                hashtab[hashval] = np1->next;
            else 
                /* in the middle or at the end? */
                np2->next = np1->next;
            free(np1);
            return;
        }
}
