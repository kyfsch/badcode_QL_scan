
void remove_mdb_entry(unsigned int mdb_id, unsigned int lag_port) {
    // Remove entry from hashed table
    hash_table_remove(mdb_id);
    
    // Remove entry from CAM table
    cam_table_remove(mdb_id);
    
    // Check if lag_port is specified
    if (lag_port) {
        // Remove entry from hash_slave table
        hash_slave_table_remove(mdb_id, lag_port);
    }
}


In this example, `hash_table_remove()` and `cam_table_remove()` are assumed to be functions for removing entries from the hashed table and CAM table, respectively. `hash_slave_table_remove()` is assumed to be a function for removing entries from the hash_slave table for LAG ports.