#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include <cassert>
#include <iostream>

using namespace std;
using namespace leveldb;

int main()
{
    // open database
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(options, "testdb", &db);
    // status
    assert(status.ok());

    WriteOptions wo;
    wo.sync = true;
    status = db->Put(wo, "KeyNameExample", "ValueExample");
    assert(status.ok());
    string res;
    status = db->Get(ReadOptions(), "KeyNameExample", &res);
    if (status.ok())
    {
        // batch write
        leveldb::WriteBatch bt;
        bt.Delete("KeyNameExample");
        bt.Put("KeyExample", "test");
        bt.Put("KeyExample2", "value2");
        status = db->Write(WriteOptions(), &bt);
        assert(status.ok());
    }
    status = db->Get(ReadOptions(), "KeyExample", &res);
    cout << "KeyExample: " << res << endl;

    // iteration
    cout << "iter: " << endl;
    leveldb::Iterator *it = db->NewIterator(ReadOptions());
    for (it->SeekToFirst(); it->Valid(); it->Next())
    {
        cout << it->key().ToString() << ": " << it->value().ToString() << endl;
    }
    cout << endl;
    assert(it->status().ok());
    delete it;

    // snapshot 
    ReadOptions rop;
    rop.snapshot = db->GetSnapshot();
    status = db->Put(WriteOptions(), "keyExample3", "value3");
    assert(status.ok());
    cout << "snapshot iter: " << endl;
    leveldb::Iterator *sit = db->NewIterator(rop);
    for (sit->SeekToFirst(); sit->Valid(); sit->Next())
    {
        cout << sit->key().ToString() << ": " << sit->value().ToString() << endl;
    }
    cout << endl;
    delete sit;
    db->ReleaseSnapshot(rop.snapshot);

    // reverse iteration
    cout << "reverse iter: " << endl;
    leveldb::Iterator *rit = db->NewIterator(ReadOptions());
    for (rit->SeekToLast(); rit->Valid(); rit->Prev())
    {
        cout << rit->key().ToString() << ": " << rit->value().ToString() << endl;
    }
    cout << endl;
    assert(rit->status().ok());
    delete rit;

    // comparator
    // compress
    // cache

    // block
    // meta block
    // 

    delete db;
    return 0;
}
