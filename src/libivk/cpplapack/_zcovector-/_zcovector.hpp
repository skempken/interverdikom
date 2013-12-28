//=============================================================================
//! (DO NOT USE) Smart-temporary Complex Double-precision Column Vector Class
class _zcovector
{
public:
  //// objects ////
  mutable long L; //!< vector size
  mutable std::complex<double>* Array; //!< 1D Array to store vector data
  
  //// constructor ////
  inline _zcovector();
  inline _zcovector(const _zcovector&);
  inline ~_zcovector(); //destructor
  
  //// io ////
  inline std::complex<double>& operator()(const long&) const;
  inline friend std::ostream& operator<<(std::ostream&, const _zcovector&);
  inline void write(const char *) const;
  
  //// calc ////
  inline friend _zrovector t(const _zcovector&);
  inline friend _zcovector conj(const _zcovector&);
  inline friend _zrovector conjt(const _zcovector&);
  inline friend double nrm2(const _zcovector&);
  inline friend long idamax(const _zcovector&);
  inline friend std::complex<double> damax(const _zcovector&);
  
  //// misc ////
  inline void destroy() const;
  
  //// unary ////
  inline friend const _zcovector& operator+(const _zcovector&);
  inline friend _zcovector operator-(const _zcovector&);

  //// + ////
  inline friend _zcovector operator+(const  zcovector&, const  zcovector&);
  inline friend _zcovector operator+(const  zcovector&, const _zcovector&);
  inline friend _zcovector operator+(const _zcovector&, const  zcovector&);
  inline friend _zcovector operator+(const _zcovector&, const _zcovector&);
  
  //// - ////
  inline friend _zcovector operator-(const  zcovector&, const  zcovector&);
  inline friend _zcovector operator-(const  zcovector&, const _zcovector&);
  inline friend _zcovector operator-(const _zcovector&, const  zcovector&);
  inline friend _zcovector operator-(const _zcovector&, const _zcovector&);

  //// * ////
  inline friend _zcovector operator*(const  zgematrix&, const  zcovector&);
  inline friend _zcovector operator*(const  zgematrix&, const _zcovector&);
  inline friend _zcovector operator*(const _zgematrix&, const  zcovector&);
  inline friend _zcovector operator*(const _zgematrix&, const _zcovector&);
  
  inline friend _zcovector operator*(const  zgbmatrix&, const  zcovector&);
  inline friend _zcovector operator*(const  zgbmatrix&, const _zcovector&);
  inline friend _zcovector operator*(const _zgbmatrix&, const  zcovector&);
  inline friend _zcovector operator*(const _zgbmatrix&, const _zcovector&);
    
  inline friend _zgematrix operator*(const _zcovector&, const  zrovector&);
  inline friend _zgematrix operator*(const _zcovector&, const _zrovector&);
  inline friend std::complex<double> operator*(const  zrovector&, const _zcovector&);
  inline friend std::complex<double> operator*(const _zrovector&, const _zcovector&);
  
  inline friend _zcovector operator*(const  zcovector&, const     double&);
  inline friend _zcovector operator*(const _zcovector&, const     double&);
  inline friend _zcovector operator*(const     double&, const  zcovector&);
  inline friend _zcovector operator*(const     double&, const _zcovector&);
  
  inline friend _zcovector operator*(const  zcovector&, const std::complex<double>&);
  inline friend _zcovector operator*(const _zcovector&, const std::complex<double>&);
  inline friend _zcovector operator*(const std::complex<double>&, const  zcovector&);
  inline friend _zcovector operator*(const std::complex<double>&, const _zcovector&);
  
  //// / ////
  inline friend _zcovector operator/(const  zcovector&, const     double&);
  inline friend _zcovector operator/(const _zcovector&, const     double&);
  inline friend _zcovector operator/(const  zcovector&, const std::complex<double>&);
  inline friend _zcovector operator/(const _zcovector&, const std::complex<double>&);
  
  //// % ////
  inline friend std::complex<double> operator%(const  zcovector&, const _zcovector&);
  inline friend std::complex<double> operator%(const _zcovector&, const  zcovector&);
  inline friend std::complex<double> operator%(const _zcovector&, const _zcovector&);
  
  //// friend classes ////
  friend class  zgematrix;
  friend class _zgematrix;
  friend class  zgbmatrix;
  friend class _zgbmatrix;
  friend class  zcovector;
  friend class  zrovector;
  friend class _zrovector;
};
