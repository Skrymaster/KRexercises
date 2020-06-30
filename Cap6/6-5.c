int undef(char * name) {
    struct nlist * np1, * np2;

    if ((np1 = lookup(name)) == NULL)
        return 1;

    for ( np1 = np2 = hashtab[hash(name)]; np1 != NULL;
          np2 = np1, np1 = np1->next ) {
        if ( strcmp(name, np1->name) == 0 ) {

            if ( np1 == np2 )
                hashtab[hash(name)] = np1->next;
            else
                np2->next = np1->next;

            free(np1->name);
            free(np1->defn);
            free(np1);

            return 0;
        }
    }

    return 1;
}