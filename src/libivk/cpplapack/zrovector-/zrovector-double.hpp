//=============================================================================
/*! zrovector*=double operator */
inline zrovector& zrovector::operator*=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::operator*=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(L, d, Array, 1);
  return *this;
}

//=============================================================================
/*! zrovector/=double operator */
inline zrovector& zrovector::operator/=(const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] zrovector::operator/=(const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zdscal_(L, 1./d, Array, 1);
  return *this;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//=============================================================================
/*! zrovector*double operator */
inline _zrovector operator*(const zrovector& vec, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const zrovector&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  zrovector newvec(vec.L);
  for(long i=0; i<vec.L; i++){ newvec.array[i] =vec.Array[i]*d; }
  
  return _(newvec);
}

//=============================================================================
/*! zrovector/double operator */
inline _zrovector operator/(const zrovector& vec, const double& d)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator/(const zrovector&, const double&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
  double inv_d(1./d);
  zrovector newvec(vec.L);
  for(long i=0; i<vec.L; i++){ newvec.array[i] =vec.Array[i]*inv_d; }
  
  return _(newvec);
}
