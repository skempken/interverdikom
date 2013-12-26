//=============================================================================
/*! destroy all the matrix data */
inline void _zssmatrix::destroy() const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zssmatrix::destroy() const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zssmatrix::destroy() "
            << " An array at " << Array
            << " is going to be destroyed." << std::endl;
#endif//CPPL_DEBUG
  
  delete [] Array;
  delete [] Indx;
  delete [] Jndx;
}

