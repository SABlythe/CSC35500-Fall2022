#include <iostream>
#include <cstdlib>

#include <sys/shm.h>

using namespace std;

int main(int argc, char *argv[])
{
  if (argc != 2)
    {
      cerr << "Usage: " << argv[0] << " <key number>" << endl;
      return 1;
    }

  int myKeyVal = atoi (argv[1]);

  int shm_id = shmget(myKeyVal, 1024 /* 1KB */, 0);

  if (shm_id==-1)
    {
      cerr << "shmget() failed with errno = ";
      cerr << errno << endl;
      return 2;
    }

  int *sharedValuePtr;
  sharedValuePtr = (int *) shmat(shm_id, NULL, 0);

  if (sharedValuePtr == (int *) -1)
    {
      cerr << "shmat() failed" << endl;
      return 3;
    }

  int valueRead = sharedValuePtr[0];
  cout << "read: " << valueRead << endl;
  
  int detatch_status = shmdt(sharedValuePtr);
  if (detatch_status != 0)
    {
      cerr << "shmdt() failed" << endl;
      return 4;
    }
  
  return 0;
}






    
