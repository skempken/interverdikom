//=============================================================================
//! Real Double-precision Row Vector Class
class drovector
{
private:
  //// objects ////
  long L; //!< vector size (NOT accessible)
  double* Array; //!< 1D array to store vector data (NOT accessible)

public:
  //// const references ////
  long const& l; //!< vector size (readable)
  double* const &array; //!< 1D array to store vector data (readable)
  
  //// constructor ////
  inline drovector();
  inline drovector(const drovector&);
  inline drovector(const _drovector&);
  inline drovector(const long&);
  inline drovector(const char*);
  inline ~drovector(); //destructor
  
  //// cast ////
  inline operator _zrovector();
  
  //// io ////
  inline double& operator()(const long&);
  inline double operator()(const long&) const;
  inline void set(const long&, const double&) const;
  inline friend std::ostream& operator<<(std::ostream&, const drovector&);
  inline void write(const char *) const;
  inline void read(const char *);
 
  //// calc ////
  inline friend _dcovector t(const drovector&);
  inline friend double nrm2(const drovector&);
  inline friend long idamax(const drovector&);
  inline friend double damax(const drovector&);

  //// misc ////
  inline void clear();
  inline void zero();
  inline void chsign();
  inline void copy(const drovector&);
  inline void shallow_copy(const _drovector&);
  inline void resize(const long&);
  inline friend void swap(drovector&, drovector&);
  inline friend _drovector _(drovector&);
  
  //// unary ////
  inline friend const drovector& operator+(const drovector&);
  inline friend _drovector operator-(const drovector&);
  
  //// operators with drovector ////
  inline drovector& operator=(const drovector&);
  inline drovector& operator+=(const drovector&);
  inline drovector& operator-=(const drovector&);
  //// operators with _drovector ////
  inline drovector& operator=(const _drovector&);
  inline drovector& operator+=(const _drovector&);
  inline drovector& operator-=(const _drovector&);
  //// operators with double ////
  inline drovector& operator*=(const double&);
  inline drovector& operator/=(const double&);
  
  //// + ////
  inline friend _drovector operator+(const  drovector&, const  drovector&);
  inline friend _drovector operator+(const  drovector&, const _drovector&);
  inline friend _drovector operator+(const _drovector&, const  drovector&);
  
  //// - ////
  inline friend _drovector operator-(const  drovector&, const  drovector&);
  inline friend _drovector operator-(const  drovector&, const _drovector&);
  inline friend _drovector operator-(const _drovector&, const  drovector&);
  
  //// * ////
  inline friend _drovector operator*(const  drovector&, const  dgematrix&);
  inline friend _drovector operator*(const  drovector&, const _dgematrix&);
  inline friend _drovector operator*(const  drovector&, const _dgbmatrix&);
  inline friend _drovector operator*(const  drovector&, const  dgbmatrix&);
  inline friend _drovector operator*(const  drovector&, const  dsymatrix&);
  inline friend _drovector operator*(const  drovector&, const _dsymatrix&);
  inline friend _drovector operator*(const  drovector&, const  dssmatrix&);
  inline friend _drovector operator*(const  drovector&, const _dssmatrix&);
  
  inline friend _drovector operator*(const  drovector&, const     double&);
  inline friend _drovector operator*(const     double&, const  drovector&);
  
  inline friend _dgematrix operator*(const  dcovector&, const  drovector&);
  inline friend _dgematrix operator*(const _dcovector&, const  drovector&);
  inline friend     double operator*(const  drovector&, const  dcovector&);
  inline friend     double operator*(const  drovector&, const _dcovector&);
  
  //// / ////
  inline friend _drovector operator/(const  drovector&, const     double&);

  //// % ////
  inline friend     double operator%(const  drovector&, const  drovector&);
  inline friend     double operator%(const  drovector&, const _drovector&);
  inline friend     double operator%(const _drovector&, const  drovector&);
  
  //// friend classes ////
  friend class  dgematrix;
  friend class _dgematrix;
  friend class  dgbmatrix;
  friend class _dgbmatrix;
  friend class  dsymatrix;
  friend class _dsymatrix;
  friend class  dssmatrix;
  friend class _dssmatrix;
  friend class  dcovector;
  friend class _dcovector;
  friend class _drovector;
};
