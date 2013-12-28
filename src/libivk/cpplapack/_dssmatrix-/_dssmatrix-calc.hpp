//=============================================================================
/*! return transposed _dssmatrix */
inline _dssmatrix t(const _dssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] t(const _dssmatrix&)"
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
inline void idamax(long& i, long& j, const _dssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] idamax(long&, long&, const _dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  long index( idamax_(mat.VOL, mat.Array, 1) -1 );
  i =mat.Indx[index];
  j =mat.Jndx[index];
  
  mat.destroy();
}

//=============================================================================
/*! return its largest absolute value */
inline double damax(const _dssmatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] damax(const _dssmatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double val( mat.Array[idamax_(mat.VOL, mat.Array, 1) -1] );
  
  mat.destroy();
  return val;
}
