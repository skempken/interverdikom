//============================================================================
/*! cast operator to _zssmatrix */
inline _dssmatrix::operator _zssmatrix()
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] _dssmatrix::operator _zssmatrix()"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zssmatrix newmat(M,N,CAP);
  for(long c=0; c<VOL; c++){
    newmat.fput(Indx[c], Jndx[c], std::complex<double>(Array[c],0.0));
  }
  
#ifdef  CPPL_DEBUG
  std::cerr << "# [NOTE] _dssmatrix::operator _zssmatrix() "
            << "A new casted matrix at " << newmat.array 
            << " has been made." << std::endl;
#endif//CPPL_DEBUG
  
  destroy();
  return _(newmat);
}
