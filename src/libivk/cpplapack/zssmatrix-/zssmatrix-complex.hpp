//=============================================================================
/*! zssmatrix*=std::complex<double> operator */
inline zssmatrix& zssmatrix::operator*=(const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::operator*=(const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(VOL, d, Array, 1);
  return *this;
}

//=============================================================================
/*! zssmatrix/=std::complex<double> operator */
inline zssmatrix& zssmatrix::operator/=(const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::operator/=(const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zscal_(VOL, 1./d, Array, 1);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! zssmatrix*std::complex<double> operator */
inline _zssmatrix operator*(const zssmatrix& mat, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zssmatrix&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zssmatrix newmat(mat.M, mat.N, mat.CAP);
  
  for(long c=0; c<mat.VOL; c++){
    newmat.fput(mat.Indx[c], mat.Jndx[c], mat.Array[c]*d);
  }
  
  return _(newmat);
}

//=============================================================================
/*! zssmatrix/std::complex<double> operator */
inline _zssmatrix operator/(const zssmatrix& mat, const std::complex<double>& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const zssmatrix&, const std::complex<double>&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  std::complex<double> inv_d(1./d);
  zssmatrix newmat(mat.M, mat.N, mat.CAP);
  
  for(long c=0; c<mat.VOL; c++){
    newmat.fput(mat.Indx[c], mat.Jndx[c], mat.Array[c]*inv_d);
  }
  
  return _(newmat);
}
