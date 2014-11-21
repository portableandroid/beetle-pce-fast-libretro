#ifndef __MDFN_CDACCESS_IMAGE_H
#define __MDFN_CDACCESS_IMAGE_H

#include <map>

class Stream;

struct CDRFILE_TRACK_INFO
{
   int32 LBA;

   uint32 DIFormat;
   uint8 subq_control;

   int32 pregap;
   int32 pregap_dv;

   int32 postgap;

   int32 index[2];

   int32 sectors; // Not including pregap sectors!
   Stream* fp;
   bool FirstFileInstance;
   bool RawAudioMSBFirst;
   long FileOffset;
   unsigned int SubchannelMode;

   uint32 LastSamplePos;
};

class CDAccess_Image : public CDAccess
{
public:

   CDAccess_Image(const char* path);
   virtual ~CDAccess_Image();

   virtual void Read_Raw_Sector(uint8* buf, int32 lba);

   virtual void Read_TOC(CDUtility_TOC* toc);

   virtual bool Is_Physical(void) throw();

   virtual void Eject(bool eject_status);
private:

   int32 NumTracks;
   int32 FirstTrack;
   int32 LastTrack;
   int32 total_sectors;
   uint8 disc_type;
   CDRFILE_TRACK_INFO Tracks[100]; // Track #0(HMM?) through 99

   std::string base_dir;

   void ImageOpen(const char* path);
   void Cleanup(void);

   // MakeSubPQ will OR the simulated P and Q subchannel data into SubPWBuf.
   void MakeSubPQ(int32 lba, uint8* SubPWBuf);

   void ParseTOCFileLineInfo(CDRFILE_TRACK_INFO* track, const int tracknum,
                             const std::string &filename, const char* binoffset, const char* msfoffset,
                             const char* length, std::map<std::string, Stream*> &toc_streamcache);
   uint32 GetSectorCount(CDRFILE_TRACK_INFO* track);
};


#endif