//=============================================================================
//! Complex Double-precision Column Vector Class
class zcovector
{
private:
  //// objects ////
  long L; //!< vector size (NOT accessible)
  std::complex<double>* Array; //!< 1D array to store vector data (NOT accessible)

public:
  //// const references ////
  long const& l; //!< vector size (readable)
  std::complex<double>* const& array; //!< 1D array to store vector data (readable)
  
  //// constructor ////
  inline zcovector();
  inline zcovector(const zcovector&);
  inline zcovector(const _zcovector&);
  inline zcovector(const long&);
  inline zcovector(const char*);
  inline ~zcovector(); //destructor
  
  //// io ////
  inline std::complex<double>& operator()(const long&);
  inline std::complex<double> operator()(const long&) const;
  inline void set(const long&, const std::complex<double>&) const;
  inline friend std::ostream& operator<<(std::ostream&, const zcovector&);
  inline void write(const char *) const;
  inline void read(const char *);
  
  //// calc ////
  inline friend _zrovector t(const zcovector&);
  inline friend _zcovector conj(const zcovector&);
  inline friend _zrovector conjt(const zcovector&);
  inline friend double nrm2(const zcovector&);
  inline friend long idamax(const zcovector&);
  inline friend std::complex<double> damax(const zcovector&);
  
  //// misc ////
  inline void clear();
  inline void zero();
  inline void chsign();
  inline void copy(const zcovector&);
  inline void shallow_copy(const _zcovector&);
  inline void resize(const long&);
  inline friend void swap(zcovector&, zcovector&);
  inline friend _zcovector _(zcovector&);
  
  //// unary ////
  inline friend const zcovector& operator+(const zcovector&);
  inline friend _zcovector operator-(const zcovector&);
  
  //// operators with zcovector ////
  inline zcovector& operator=(const zcovector&);
  inline zcovector& operator+=(const zcovector&);
  inline zcovector& operator-=(const zcovector&);
  //// operators with _zcovector ////
  inline zcovector& operator=(const _zcovector&);
  inline zcovector& operator+=(const _zcovector&);
  inline zcovector& operator-=(const _zcovector&);
  //// operators with double ////
  inline zcovector& operator*=(const double&);
  inline zcovector& operator/=(const double&);
  //// operators with std::complex<double> ////
  inline zcovector& operator*=(const std::complex<double>&);
  inline zcovector& operator/=(const std::complex<double>&);

  //// + ////
  inline friend _zcovector operator+(const  zcovector&, const  zcovector&);
  inline friend _zcovector operator+(const  zcovector&, const _zcovector&);
  inline friend _zcovector operator+(const _zcovector&, const  zcovector&);
  
  //// - ////
  inline friend _zcovector operator-(const  zcovector&, const  zcovector&);
  inline friend _zcovector operator-(const  zcovector&, const _zcovector&);
  inline friend _zcovector operator-(const _zcovector&, const  zcovector&);
  
  //// * ////
  inline friend _zcovector operator*(const  zgematrix&, const  zcovector&);
  inline friend _zcovector operator*(const _zgematrix&, const  zcovector&);
  inline friend _zcovector operator*(const  zgbmatrix&, const  zcovector&);
  inline friend _zcovector operator*(const _zgbmatrix&, const  zcovector&);
  inline friend _zcovector operator*(const  zhematrix&, const  zcovector&);
  inline friend _zcovector operator*(const _zhematrix&, const  zcovector&);
  inline friend _zcovector operator*(const  zssmatrix&, const  zcovector&);
  inline friend _zcovector operator*(const _zssmatrix&, const  zcovector&);
  
  inline friend _zgematrix operator*(const  zcovector&, const _zrovector&);
  inline friend _zgematrix operator*(const  zcovector&, const  zrovector&);
  
  inline friend std::complex<double> operator*(const _zrovector&, const  zcovector&);
  inline friend std::complex<double> operator*(const  zrovector&, const  zcovector&);
  
  inline friend _zcovector operator*(const     double&, const  zcovector&);
  inline friend _zcovector operator*(const  zcovector&, const     double&);
  
  inline friend _zcovector operator*(const std::complex<double>&, const  zcovector&);
  inline friend _zcovector operator*(const  zcovector&, const std::complex<double>&);
  
  //// / ////
  inline friend _zcovector operator/(const  zcovector&, const     double&);
  inline friend _zcovector operator/(const  zcovector&, const std::complex<double>&);
  
  //// % ////
  inline friend std::complex<double> operator%(const  zcovector&, const  zcovector&);
  inline friend std::complex<double> operator%(const  zcovector&, const _zcovector&);
  inline friend std::complex<double> operator%(const _zcovector&, const  zcovector&);
  
  //// friend class ////
  friend class  zgematrix;
  friend class _zgematrix;
  friend class  zgbmatrix;
  friend class _zgbmatrix;
  friend class  zhematrix;
  friend class _zhematrix;
  friend class _zcovector;
  friend class  zrovector;
  friend class _zrovector;  
};
