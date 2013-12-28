//=============================================================================
/*! destroy all the matrix data */
inline void _dgematrix::destroy() const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dgematrix::destroy() const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dgematrix::destroy() "
            << " An array at " << Array
            << " is going to be destroyed." << std::endl;
#endif//CPPL_DEBUG
  
  delete [] Array;
  delete [] Darray;
}

