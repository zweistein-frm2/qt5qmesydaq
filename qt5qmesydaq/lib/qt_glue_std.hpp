#pragma once

#include <ostream>
#include <QtCore/QRectF>
#include <QtCore/QString>
#include <QtCore/QMap>
inline std::ostream& operator<<(std::ostream& p, const QRectF& r) {
	p << "QRectF(x" << r.x() << ",y:" << r.y() << ", width:" << r.width() << ", height:" << r.height() << ")";
	return p;
}

inline std::ostream& operator<<(std::ostream& p, const QPoint &qp) {
	p << "QPoint(" << qp.x() << "," << qp.y() << ")";
	return p;
}

inline std::ostream& operator<<(std::ostream& p,const QString& s) {
	p<<s.toStdString();
	return p;
}


inline std::ostream& operator<<(std::ostream& p, const QVariantList& qvl) {
#pragma message("ALANGHOF : todo: strm QVariant  overload op")
	return p;
}


inline std::ostream& operator<<(std::ostream& p, const QList<QVariantList> & lqv) {
#pragma message("ALANGHOF : todo: strm  QList<QVariant>  overload op")
	return p;
}

inline std::ostream& operator<<(std::ostream& p, const QMap<quint16, quint16>& m) {
	auto stdm = m.toStdMap();

	for (auto& i : stdm) {
		p << "[" << i.first << ":" << i.second << "]";
	}
	return p;
}

#ifdef simpleLogger_hpp__
 inline boost::log::BOOST_LOG_VERSION_NAMESPACE::basic_record_ostream<char>& operator<<(boost::log::BOOST_LOG_VERSION_NAMESPACE::basic_record_ostream<char>& p, const QRectF& r) {
	p << "QRectF(x" << r.x() << ",y:" << r.y() << ", width:" << r.width() << ", height:" << r.height() << ")";
	return p;
}

 inline boost::log::BOOST_LOG_VERSION_NAMESPACE::basic_record_ostream<char>& operator<<(boost::log::BOOST_LOG_VERSION_NAMESPACE::basic_record_ostream<char>& p, const QPoint &qp) {
	 p << "QPoint(" << qp.x() << "," << qp.y() << ")";
	 return p;
 }


inline boost::log::BOOST_LOG_VERSION_NAMESPACE::basic_record_ostream<char>& operator<<(boost::log::BOOST_LOG_VERSION_NAMESPACE::basic_record_ostream<char>& p, const QString& s) {
	p << s.toStdString();
	return p;
}

inline boost::log::BOOST_LOG_VERSION_NAMESPACE::basic_record_ostream<char>& operator<<(boost::log::BOOST_LOG_VERSION_NAMESPACE::basic_record_ostream<char>& p, const QVariantList &qvl) {
#pragma message("ALANGHOF : todo: QVariant  overload op")
	return p;
}

inline boost::log::BOOST_LOG_VERSION_NAMESPACE::basic_record_ostream<char>& operator<<(boost::log::BOOST_LOG_VERSION_NAMESPACE::basic_record_ostream<char>& p, const QList<QVariantList>& lqv) {
#pragma message("ALANGHOF : todo : QList<QVariant>  overload op")
	return p;
}

inline boost::log::BOOST_LOG_VERSION_NAMESPACE::basic_record_ostream<char>& operator<<(boost::log::BOOST_LOG_VERSION_NAMESPACE::basic_record_ostream<char>& p, const QMap<quint16,quint16> &m) {
	auto stdm = m.toStdMap();
	for (auto& i : stdm) {
		p << "[" << i.first << ":" << i.second << "]";
	}
	return p;
}


#endif
