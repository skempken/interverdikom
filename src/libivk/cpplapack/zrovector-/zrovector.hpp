//=============================================================================
//! Complex Double-precision Row Vector Class
class zrovector
{
private:
  //// objects ////
  long L; //!< vector size (NOT accessible)
  std::complex<double>* Array; //!< 1D array to store vector data (NOT accessible)

public:
  //// const references ////
  long const& l; //!< vector size (readable)
  std::complex<double>* const &array; //!< 1D array to store vector data (readable)
  
  //// constructor ////
  inline zrovector();
  inline zrovector(const zrovector&);
  inline zrovector(const _zrovector&);
  inline zrovector(const long&);
  inline zrovector(const char*);
  inline ~zrovector(); //destructor
  
  //// io ////
  inline std::complex<double>& operator()(const long&);
  inline std::complex<double> operator()(const long&) const;
  inline void set(const long&, const std::complex<double>&) const;
  inline friend std::ostream& operator<<(std::ostream&, const zrovector&);
  inline void write(const char *) const;
  inline void read(const char *);
 
  //// calc ////
  inline friend _zcovector t(const zrovector&);
  inline friend _zrovector conj(const zrovector&);
  inline friend _zcovector conjt(const zrovector&);
  inline friend double nrm2(const zrovector&);
  inline friend long idamax(const zrovector&);
  inline friend std::complex<double> damax(const zrovector&);

  //// misc ////
  inline void clear();
  inline void zero();
  inline void chsign();
  inline void copy(const zrovector&);
  inline void shallow_copy(const _zrovector&);
  inline void resize(const long&);
  inline friend void swap(zrovector&, zrovector&);
  inline friend _zrovector _(zrovector&);
  
  //// unary ////
  inline friend const zrovector& operator+(const zrovector&);
  inline friend _zrovector operator-(const zrovector&);
  
  //// operators with zrovector ////
  inline zrovector& operator=(const zrovector&);
  inline zrovector& operator+=(const zrovector&);
  inline zrovector& operator-=(const zrovector&);
  //// operators with _zrovector ////
  inline zrovector& operator=(const _zrovector&);
  inline zrovector& operator+=(const _zrovector&);
  inline zrovector& operator-=(const _zrovector&);
  //// operators with double ////
  inline zrovector& operator*=(const double&);
  inline zrovector& operator/=(const double&);
  //// operators with std::complex<double> ////
  inline zrovector& operator*=(const std::complex<double>&);
  inline zrovector& operator/=(const std::complex<double>&);
  
  //// + ////
  inline friend _zrovector operator+(const  zrovector&, const  zrovector&);
  inline friend _zrovector operator+(const  zrovector&, const _zrovector&);
  inline friend _zrovector operator+(const _zrovector&, const  zrovector&);
  
  //// - ////
  inline friend _zrovector operator-(const  zrovector&, const  zrovector&);
  inline friend _zrovector operator-(const  zrovector&, const _zrovector&);
  inline friend _zrovector operator-(const _zrovector&, const  zrovector&);
  
  //// * ////
  inline friend _zrovector operator*(const  zrovector&, const  zgematrix&);
  inline friend _zrovector operator*(const  zrovector&, const _zgematrix&);
  inline friend _zrovector operator*(const  zrovector&, const _zgbmatrix&);
  inline friend _zrovector operator*(const  zrovector&, const  zgbmatrix&);
  inline friend _zrovector operator*(const  zrovector&, const  zhematrix&);
  inline friend _zrovector operator*(const  zrovector&, const _zhematrix&);
  inline friend _zrovector operator*(const  zrovector&, const  zssmatrix&);
  inline friend _zrovector operator*(const  zrovector&, const _zssmatrix&);
  
  inline friend _zgematrix operator*(const  zcovector&, const  zrovector&);
  inline friend _zgematrix operator*(const _zcovector&, const  zrovector&);
  
  inline friend std::complex<double> operator*(const  zrovector&, const  zcovector&);
  inline friend std::complex<double> operator*(const  zrovector&, const _zcovector&);
  
  inline friend _zrovector operator*(const  zrovector&, const     double&);
  inline friend _zrovector operator*(const     double&, const  zrovector&);
  
  inline friend _zrovector operator*(const  zrovector&, const std::complex<double>&);
  inline friend _zrovector operator*(const std::complex<double>&, const  zrovector&);
  
  //// / ////
  inline friend _zrovector operator/(const  zrovector&, const     double&);
  inline friend _zrovector operator/(const  zrovector&, const std::complex<double>&);

  //// % ////
  inline friend std::complex<double> operator%(const  zrovector&, const  zrovector&);
  inline friend std::complex<double> operator%(const  zrovector&, const _zrovector&);
  inline friend std::complex<double> operator%(const _zrovector&, const  zrovector&);
  
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
  friend class _zrovector;
};
