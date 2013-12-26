//=============================================================================
/*! dssmatrix*=double operator */
inline dssmatrix& dssmatrix::operator*=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::operator*=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(VOL, d, Array, 1);
  return *this;
}

//=============================================================================
/*! dssmatrix/=double operator */
inline dssmatrix& dssmatrix::operator/=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] dssmatrix::operator/=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dscal_(VOL, 1./d, Array, 1);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! dssmatrix*double operator */
inline _dssmatrix operator*(const dssmatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const dssmatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  dssmatrix newmat(mat.M, mat.N, mat.CAP);
  
  for(long c=0; c<mat.VOL; c++){
    newmat.fput(mat.Indx[c], mat.Jndx[c], mat.Array[c]*d);
  }
  
  return _(newmat);
}

//=============================================================================
/*! dssmatrix/double operator */
inline _dssmatrix operator/(const dssmatrix& mat, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const dssmatrix&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double inv_d(1./d);
  dssmatrix newmat(mat.M, mat.N, mat.CAP);
  
  for(long c=0; c<mat.VOL; c++){
    newmat.fput(mat.Indx[c], mat.Jndx[c], mat.Array[c]*inv_d);
  }
  
  return _(newmat);
}
