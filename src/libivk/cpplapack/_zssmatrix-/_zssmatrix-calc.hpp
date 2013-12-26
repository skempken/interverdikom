//=============================================================================
/*! return transposed _zssmatrix */
inline _zssmatrix t(const _zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long* mat_Indx(mat.Indx);
  mat.Indx =mat.Jndx;
  mat.Jndx =mat_Indx;
  
  return mat;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! search the index of element having the largest absolute value
  in 0-based numbering system */
inline void idamax(long& i, long& j, const _zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] idamax(long&, long&, const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long index( izamax_(mat.VOL, mat.Array, 1) -1 );
  i =mat.Indx[index];
  j =mat.Jndx[index];
  
  mat.destroy();
}

//=============================================================================
/*! return its largest absolute value */
inline std::complex<double> damax(const _zssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] damax(const _zssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::complex<double> val( mat.Array[izamax_(mat.VOL, mat.Array, 1) -1] );
  mat.destroy();
  return val;
}
