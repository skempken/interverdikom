//=============================================================================
/*! zssmatrix*=double operator */
inline zssmatrix& zssmatrix::operator*=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::operator*=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(VOL, d, Array, 1);
  return *this;
}

//=============================================================================
/*! zssmatrix/=double operator */
inline zssmatrix& zssmatrix::operator/=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zssmatrix::operator/=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(VOL, 1./d, Array, 1);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! zssmatrix*double operator */
inline _zssmatrix operator*(const zssmatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zssmatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zssmatrix newmat(mat.M, mat.N, mat.CAP);
  
  for(long c=0; c<mat.VOL; c++){
    newmat.fput(mat.Indx[c], mat.Jndx[c], mat.Array[c]*d);
  }
  
  return _(newmat);
}

//=============================================================================
/*! zssmatrix/double operator */
inline _zssmatrix operator/(const zssmatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const zssmatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double inv_d(1./d);
  zssmatrix newmat(mat.M, mat.N, mat.CAP);
  for(long c=0; c<mat.VOL; c++){
    newmat.fput(mat.Indx[c], mat.Jndx[c], mat.Array[c]*inv_d);
  }
  
  return _(newmat);
}
