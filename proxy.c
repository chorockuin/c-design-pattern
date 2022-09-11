typedef struct {
    void (*write_string_to_database)(void *this, char *string);
} DBServer;

void DBServer_write_string_to_database(void *this, char *string) {
    printf("write string(%s) to real database\n", string);
}



typedef struct {
    DBServer base;
    char cached_string[128];
    void (*update_database)(void *this);
} DBServerProxy;

void DBServerProxy_write_string_to_database(void *this, char *string) {
    DBServerProxy *proxy = (DBServerProxy *)this;
    memcpy(proxy->cached_string, string, sizeof(proxy->cached_string));
    proxy->cached_string[127] = 0;
    printf("cached string(%s)\n", proxy->cached_string);
}

void DBServerProxy_update_database(void *this) {
    DBServerProxy *proxy = (DBServerProxy *)this;
    printf("write string(%s) to real database\n", proxy->cached_string);
}



void proxy() {
    printf("======================== proxy\n");
    {
        DBServer *db = (DBServer *)malloc(sizeof(DBServer));
        db->write_string_to_database = DBServer_write_string_to_database;

        db->write_string_to_database(db, "design pattern");
        db->write_string_to_database(db, "sucks");

        free(db);
    }
    {
        DBServer *db = (DBServer *)malloc(sizeof(DBServerProxy));
        db->write_string_to_database = DBServerProxy_write_string_to_database;
        DBServerProxy *proxy = (DBServerProxy *)db;
        proxy->update_database = DBServerProxy_update_database;

        db->write_string_to_database(db, "design pattern");
        db->write_string_to_database(db, "sucks");
        proxy->update_database(proxy);

        free(proxy);
    }
}