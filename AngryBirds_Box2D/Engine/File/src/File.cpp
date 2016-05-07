
#include <assert.h>
#include "File.h"

FileError File::open( FileHandle &fh, const char * const fileName, FileMode mode )
{
   DWORD fileMode;
   

   fileMode = privGetFileDesiredAccess( mode );

   if( mode == FILE_WRITE || mode == FILE_READ_WRITE )
   {
   fh = CreateFile(  fileName,                // name of the write
                     fileMode,          // open for writing
                     0,                      // do not share
                     0,                   // default security
                     CREATE_ALWAYS,             // create new file only
                     FILE_ATTRIBUTE_NORMAL,  // normal file
                     NULL);    
   }
   else if ( mode == FILE_READ )
   {
   fh = CreateFile(  fileName,                // name of the write
                     fileMode,          // open for writing
                     0,                      // do not share
                     0,                   // default security
                     OPEN_EXISTING,             // create new file only
                     FILE_ATTRIBUTE_NORMAL,  // normal file
                     NULL);  
   }
   else
   {
      fh = INVALID_HANDLE_VALUE;
   }


   if ( fh == INVALID_HANDLE_VALUE)
   {
      return FILE_OPEN_FAIL;
   }
   else
   {
      return FILE_SUCCESS;
   }

}


DWORD File::privGetFileDesiredAccess( FileMode mode )
{
   DWORD out(0);

   switch( mode )
   {
   case FILE_READ:
         out = GENERIC_READ;
         break;
   case FILE_WRITE:
         out = GENERIC_WRITE;
         break;
   case FILE_READ_WRITE:
         out = GENERIC_READ | GENERIC_WRITE;
         break;
   default:
         assert(0);
         break;
   }

   return out;
}

FileError File::close( const FileHandle fh )
{
   if( CloseHandle( fh ) )
   {
      return FILE_SUCCESS;
   }
   else
   {
      return FILE_CLOSE_FAIL;
   }
}

FileError File::write( FileHandle fh, const void * const buffer, const size_t inSize )
{
   DWORD numWritten;
   if( WriteFile( fh, buffer, inSize, &numWritten, 0) )
   {
      return FILE_SUCCESS;
   }
   else
   {
      return FILE_WRITE_FAIL;
   }
}

FileError File::read( FileHandle fh,  void * const buffer, const size_t inSize )
{
   DWORD numRead;
   if( ReadFile( fh, buffer, inSize, &numRead, 0) )
   {
      return FILE_SUCCESS;
   }
   else
   {
      return FILE_READ_FAIL;
   }
}


FileError File::seek( FileHandle fh, FileSeek seek, int offset )
{
   DWORD seekOrigin;

   seekOrigin = privGetSeek( seek );

   if ( SetFilePointer( fh, offset, 0, seekOrigin ) == INVALID_SET_FILE_POINTER )
   {
      return FILE_SEEK_FAIL;
   }
   else 
   {
      return FILE_SUCCESS;
   }

}


DWORD File::privGetSeek( FileSeek seek )
{
   DWORD out=0xCCCCCCCC;

   switch( seek )
   {
   case FILE_SEEK_BEGIN:
      out = FILE_BEGIN;
      break;
   case FILE_SEEK_CURRENT:
      out = FILE_CURRENT;
      break;
   case FILE_SEEK_END:
      out = FILE_END;
      break;
   default:
      assert(0);
   }

   return out;
}


FileError File::tell( FileHandle fh, int &offset )
{
   offset = SetFilePointer( fh, 0, 0, FILE_CURRENT );

   if ( offset  == INVALID_SET_FILE_POINTER )
   {
      return FILE_TELL_FAIL;
   }
   else 
   {
      return FILE_SUCCESS;
   }

}


FileError File::flush( FileHandle fh )
{
   if( FlushFileBuffers( fh ) )
   {
      return FILE_SUCCESS;
   }
   else
   {
      return FILE_FLUSH_FAIL;
   }
}