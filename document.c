#include <gtk/gtk.h>
#include "document.h"

G_DEFINE_TYPE (Document, document, DOCUMENT_TYPE);

#define DOCUMENT_GET_PRIVATE(o)\
    (G_TYPE_INSTANCE_GET_PRIVATE ((o), DOCUMENT_TYPE, DocumentPrivate))

struct _DocumentPrivate {
};


static void
document_dispose (Document *self)
{
}

static void
document_finalize (Document *self)
{
}

static void
document_init (Document *self)
{
    DocumentPrivate *priv;

    priv = DOCUMENT_GET_PRIVATE (self);
}

static void
document_class_init (DocumentClass *self_class)
{
    GObjectClass *object_class = G_OBJECT_CLASS (self_class);

    g_type_class_add_private (self_class, sizeof (DocumentPrivate));
    object_class->dispose = (void (*) (GObject *object)) document_dispose;
    object_class->finalize = (void (*) (GObject *object)) document_finalize;
}

