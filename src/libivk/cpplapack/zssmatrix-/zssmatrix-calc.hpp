//=============================================================================
/*! return transposed zssmatrix */
inline _zssmatrix t(const zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zssmatrix newmat(mat.N,mat.M,mat.CAP);
  
  for(long c=0; c<mat.VOL; c++){
    newmat.fput(mat.Jndx[c], mat.Indx[c], mat.Array[c]);
  }
  
  return _(newmat);
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! search the index of element having the largest absolute value
  in 0-based numbering system */
inline void idamax(long& i, long& j, const zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] idamax(long&, long&, const zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long index( izamax_(mat.VOL, mat.Array, 1) -1 );
  i =mat.Indx[index];
  j =mat.Jndx[index];
}

//=============================================================================
/*! return its largest absolute value */
inline std::complex<double> damax(const zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] damax(const zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  return mat.Array[izamax_(mat.VOL, mat.Array, 1) -1];
}
