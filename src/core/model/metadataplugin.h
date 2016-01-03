#ifndef METADATAPLUGIN_H
#define METADATAPLUGIN_H

#include <qbytearray.h>

class CouchRequest;
class Item;
class ItemMetadata;

#if defined(COUCH_LIBRARY)
#  define COUCH_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define COUCH_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

class COUCH_LIBRARY_EXPORT MetadataPlugin
{
public:
    virtual ~MetadataPlugin() = default;

    virtual void buildRequest(CouchRequest *request, const Item *item) = 0;
    virtual ItemMetadata* parseReply(const QByteArray &data) = 0;
};

#endif // METADATAPLUGIN_H
