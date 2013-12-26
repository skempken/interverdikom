//=============================================================================
/*! destroy all the matrix data */
inline void _zgematrix::destroy() const
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _zgematrix::destroy() const"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _zgematrix::destroy() "
            << " An array at " << Array
            << " is going to be destroyed." << std::endl;
#endif//CPPL_DEBUG
  
  delete [] Array;
  delete [] Darray;
}
