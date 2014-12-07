#include <iostream>

#include "encrypt.h"
#include "sha256.h"
#include <vector>
#include <fstream>

using namespace rapidjson;
using namespace std;

bool check_file_exists(string file_path)
{
  ifstream sfile(file_path.c_str());
  if(sfile.good())
  {
    sfile.close();
    return true;
  }
  else
  {
    sfile.close();
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "You need to supply more arguments. Example: " << argv[0] << " download-audit <file_with_auditable_ballot.json>" << endl;
    exit(1);
  }
  
  vector<string> vargs;
  
  for(int i = 0; i < argc; ++i)
  {
      vargs.push_back(string(argv[i]));
  }
  
  
  if(vargs.at(1) == string("download-audit"))
  {
    if(vargs.size() < 3)
    {
      cout << "You need to supply more arguments. Example: " << argv[0] << " download-audit <file_with_auditable_ballot.json>" << endl;
      exit(1);
    }
    else if(vargs.size() > 3)
    {
      cout << "Error: too many arguments. " << endl;
      exit(1);
    }
    else if(!check_file_exists(vargs.at(2)))
    {
      cout << "Error: ballot file not found at path " << vargs.at(2) << endl;
      exit(1);
    }
    else
    {
      download_audit(vargs.at(2));
    }
  }
  else if(vargs.at(1) == string("download"))
  {
    if(vargs.size() < 5)
    {
      cout << "You need to supply more arguments. Example: " << argv[0] << " download <file_with_auditable_ballot.json> <public_key_file> <election_data_file>" << endl;
      exit(1);
    }
    else if(vargs.size() > 5)
    {
      cout << "Error: too many arguments " << endl;
      exit(1);
    }
    else if(!check_file_exists(vargs.at(2)))
    {
      cout << "Error: ballot file not found at path " << vargs.at(2) << endl;
      exit(1);
    }
    else if(check_file_exists(vargs.at(3)))
    {
      cout << "Error: cannot create public key file at path " << vargs.at(3)  << " as it already exists" << endl;
      exit(1);
    }
    else if(check_file_exists(vargs.at(4)))
    {
      cout << "Error: cannot create election data file at path " << vargs.at(4) << " as it already exists"  << endl;
      exit(1);
    }
    else
    {
      download(vargs.at(2),vargs.at(3), vargs.at(4));
    }
  }
  else if(vargs.at(1) == string("audit"))
  {
    if(vargs.size() < 5)
    {
      cout << "You need to supply more arguments. Example: " << argv[0] << " audit <file_with_auditable_ballot.json> <public_key_file> <election_data_file>" << endl;
      exit(1);
    }
    else if(vargs.size() > 5)
    {
      cout << "Error: too many arguments. " << endl;
      exit(1);
    }
    else if(!check_file_exists(vargs.at(2)))
    {
      cout << "Error: ballot file not found at path " << vargs.at(2) << endl;
      exit(1);
    }
    else if(!check_file_exists(vargs.at(3)))
    {
      cout << "Error: public key file not found at path " << vargs.at(3) << endl;
      exit(1);
    }
    else if(!check_file_exists(vargs.at(4)))
    {
      cout << "Error: election data file not found at path " << vargs.at(4) << endl;
      exit(1);
    }
    else
    {
      audit(vargs.at(2),vargs.at(3), vargs.at(4));
    }
  }
  else
  {
    cout << "Usage: agora-airgap [option] file..." << endl << "Options" << endl
          << "\tdownload-audit\t\t\tdownload public keys and election data, afterwards audit the ballot" << endl
          << "\tdownload\t\t\tdownload public keys and election data" << endl
          << "\taudit\t\t\t\taudit the ballot, providing the files with the public keys and election data" << endl;
  }
	return 0;
}