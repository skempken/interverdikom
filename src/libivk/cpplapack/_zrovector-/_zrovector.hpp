//=============================================================================
//! (DO NOT USE) Smart-temporary Complex Double-precision Row Vector Class
class _zrovector
{
public:
  //// objects ////
  mutable long L; //!< vector size
  mutable std::complex<double>* Array; //!< 1D Array to store vector data
  
  //// constructor ////
  inline _zrovector();
  inline _zrovector(const _zrovector&);
  inline ~_zrovector(); //destructor
  
  //// io ////
  inline std::complex<double>& operator()(const long&) const;
  inline friend std::ostream& operator<<(std::ostream&, const _zrovector&);
  inline void write(const char *) const;
  
  //// calc ////
  inline friend _zcovector t(const _zrovector&);
  inline friend _zrovector conj(const _zrovector&);
  inline friend _zcovector conjt(const _zrovector&);
  inline friend double nrm2(const _zrovector&);
  inline friend long idamax(const _zrovector&);
  inline friend std::complex<double> damax(const _zrovector&);

  //// misc ////
  inline void destroy() const;
  
  //// unary ////
  inline friend const _zrovector& operator+(const _zrovector&);
  inline friend _zrovector operator-(const _zrovector&);
  
  //// + ////
  inline friend _zrovector operator+(const  zrovector&, const  zrovector&);
  inline friend _zrovector operator+(const  zrovector&, const _zrovector&);
  inline friend _zrovector operator+(const _zrovector&, const  zrovector&);
  inline friend _zrovector operator+(const _zrovector&, const _zrovector&);
  
  //// - ////
  inline friend _zrovector operator-(const  zrovector&, const  zrovector&);
  inline friend _zrovector operator-(const  zrovector&, const _zrovector&);
  inline friend _zrovector operator-(const _zrovector&, const  zrovector&);
  inline friend _zrovector operator-(const _zrovector&, const _zrovector&);
  
  //// * ////
  inline friend _zrovector operator*(const  zrovector&, const  zgematrix&);
  inline friend _zrovector operator*(const  zrovector&, const _zgematrix&);
  inline friend _zrovector operator*(const _zrovector&, const  zgematrix&);
  inline friend _zrovector operator*(const _zrovector&, const _zgematrix&);
  
  inline friend _zrovector operator*(const  zrovector&, const  zgbmatrix&);
  inline friend _zrovector operator*(const  zrovector&, const _zgbmatrix&);
  inline friend _zrovector operator*(const _zrovector&, const  zgbmatrix&);
  inline friend _zrovector operator*(const _zrovector&, const _zgbmatrix&);
  
  inline friend _zrovector operator*(const  zrovector&, const  zhematrix&);
  inline friend _zrovector operator*(const  zrovector&, const _zhematrix&);
  inline friend _zrovector operator*(const _zrovector&, const  zhematrix&);
  inline friend _zrovector operator*(const _zrovector&, const _zhematrix&);

  inline friend _zrovector operator*(const  zrovector&, const  zssmatrix&);
  inline friend _zrovector operator*(const  zrovector&, const _zssmatrix&);
  inline friend _zrovector operator*(const _zrovector&, const  zssmatrix&);
  inline friend _zrovector operator*(const _zrovector&, const _zssmatrix&);
  
  inline friend _zgematrix operator*(const  zcovector&, const _zrovector&);
  inline friend _zgematrix operator*(const _zcovector&, const _zrovector&);
  
  inline friend std::complex<double> operator*(const _zrovector&, const  zcovector&);
  inline friend std::complex<double> operator*(const _zrovector&, const _zcovector&);
  
  inline friend _zrovector operator*(const     double&, const  zrovector&);
  inline friend _zrovector operator*(const     double&, const _zrovector&);
  inline friend _zrovector operator*(const  zrovector&, const     double&);
  inline friend _zrovector operator*(const _zrovector&, const     double&);
  
  inline friend _zrovector operator*(const std::complex<double>&, const  zrovector&);
  inline friend _zrovector operator*(const std::complex<double>&, const _zrovector&);
  inline friend _zrovector operator*(const  zrovector&, const std::complex<double>&);
  inline friend _zrovector operator*(const _zrovector&, const std::complex<double>&);
  
  //// / ////
  inline friend _zrovector operator/(const  zrovector&, const     double&);
  inline friend _zrovector operator/(const _zrovector&, const     double&);
  inline friend _zrovector operator/(const  zrovector&, const std::complex<double>&);
  inline friend _zrovector operator/(const _zrovector&, const std::complex<double>&);
  
  //// % ////
  inline friend std::complex<double> operator%(const  zrovector&, const _zrovector&);
  inline friend std::complex<double> operator%(const _zrovector&, const  zrovector&);
  inline friend std::complex<double> operator%(const _zrovector&, const _zrovector&);
  
  //// friend classes ////
  friend class  zgematrix;
  friend class _zgematrix;
  friend class  zgbmatrix;
  friend class _zgbmatrix;
  friend class  zhematrix;
  friend class _zhematrix;
  friend class  zssmatrix;
  friend class _zssmatrix;
  friend class  zcovector;
  friend class _zcovector;
  friend class  zrovector;
};
