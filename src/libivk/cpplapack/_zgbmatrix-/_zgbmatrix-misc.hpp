//=============================================================================
/*! destroy all the matrix data */
inline void _zgbmatrix::destroy() const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zgbmatrix::destroy() const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zgbmatrix::destroy() const"
            << " An array at " << Array
            << " is going to be cleared." << std::endl;
#endif//CPPL_DEBUG
  
  delete [] Array;
  delete [] Darray;
}


