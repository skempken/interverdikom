//=============================================================================
/*! destroy all the matrix data */
inline void _dssmatrix::destroy() const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dssmatrix::destroy() const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dssmatrix::destroy() "
            << " An array at " << Array
            << " is going to be destroyed." << std::endl;
#endif//CPPL_DEBUG
  
  delete [] Array;
  delete [] Indx;
  delete [] Jndx;
}
