/*----------------------------------------------------------------------------
  Motel Document
 
  application programmer's types (APT) header file
  ----------------------------------------------------------------------------
  Copyright 2011-2012 John L. Hart IV. All rights reserved.
 
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
 
  1. Redistributions of source code must retain all copyright notices,
     this list of conditions and the following disclaimer.
 
  2. Redistributions in binary form must reproduce all copyright
     notices, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
 
  THIS SOFTWARE IS PROVIDED BY John L. Hart IV "AS IS" AND ANY EXPRESS OR
  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
  NO EVENT SHALL John L. Hart IV OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
  INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
  DAMAGE.
 
  The views and conclusions contained in the software and documentation are
  those of the authors and should not be interpreted as representing official
  policies, either expressed or implied, of John L Hart IV.
  ----------------------------------------------------------------------------*/

#ifndef MOTEL_DOCUMENT_T_H
#define MOTEL_DOCUMENT_T_H

/*----------------------------------------------------------------------------
  The document parser applies many of the principals of an XML SAX parser and
  as such implements functionality that is similar to the following interfaces:

  javax.xml.parsers - SAXDocument

  org.xml.sax.helpers - DefaultHandler

  org.xml.sax - HandlerBase
  org.xml.sax - Interface ContentHandler

  org.xml.sax - Interface Locator

  These methods are provided as parser callback functions.
  ----------------------------------------------------------------------------
  SAXDocument Class differences:

  getSchema() - A schema reference is always explictly declared as a node in
  the document, as a result this method is not implemented.

  isValidating() - Documents are always validated when schemas are accessible
  to the parser, as a result this method is not implemented.

  isNamespaceAware() - The parser is always namespace aware therefore there
  is no purpose for this method.

  isXIncludeAware() - Include documents are always processed when accessible
  to the parser, as a result this method is not implemented.

  ----------------------------------------------------------------------------
  HandlerBase/DefaultHandler/ContentHandler & Locator Class differences:

  processingInstruction() - Motel documents do not have processing
  instructions. The effect of processing instructions may be achieved via
  scripts.

  unparsedEntityDecl() - Entities are not supported.

  resolveEntity() - Entities are not supported.

  skippedEntity() - Entities are not supported.

  notationDecl() - Notation declarations are not supported.

  setDocumentLocator() - These are supported as members of the document node.

  ----------------------------------------------------------------------------
  The document parser applies many of the principals of an XML DOM parser and
  as such implements functionality that is similar to the following interfaces:

  javax.xml.parsers - Class DocumentBuilderFactory
  javax.xml.parsers - Class DocumentBuilder

  org.w3c.dom - Interface Document
  org.w3c.dom - Interface Node
  ----------------------------------------------------------------------------
  DocumentBuilderFactory Class differences:

  getSchema() - A schema reference is always explictly declared as a node in
  the document, as a result this method is not implemented.

  isValidating() - Documents are always validated when schemas are accessible
  to the parser, as a result this method is not implemented.

  isNamespaceAware() - The parser is always namespace aware therefore there
  is no purpose for this method.

  isXIncludeAware() - Include documents are always processed when accessible
  to the parser, as a result this method is not implemented.

  isExpandEntityReferences() - Entities are not supported.

  isCoalescing() - CDATA nodes are not supported and therefore this capability
  is not needed.

  ----------------------------------------------------------------------------
  DocumentBuilder Class differences:

  getDOMImplementation() - Not supported at this time.
  ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
  Establish pseudo-encapsulation
  ----------------------------------------------------------------------------*/

#ifndef MUTABILITY
#define MUTABILITY const
#endif

#include "../Motel.Buffer/motel.buffer.t.h"
#include "../Motel.Stream/motel.stream.t.h"

#include "../Motel.Hrr/motel.hrr.t.h"
#include "../Motel.Url/motel.url.t.h"
#include "../Motel.file/motel.file.t.h"

/*
** Public Document members
*/

typedef enum motelDocumentMember motelDocumentMember;

enum motelDocumentMember
{
	motelDocumentMember_Result,                /*!< Data type:   (motelResult *)
                                                Description: The method result code */

	motelDocumentMember_Size,                  /*!< Data type:   (size_t *)
                                                Description: Memory currently allocated by the document object */

	motelDocumentMember_Objects,               /*!< Data type:   (unsigned long *)
                                                Description: The number of objects in the document */

	motelDocumentMember_DocumentHRR,           /*!< Data type:   (char *)
                                                Description: HRR reference to the document being parsed */

	motelDocumentMember_DocumentURL,           /*!< Data type:   (char *)
                                                Description: URL reference to the document being parsed */

	motelDocumentMember_DocumentFile,          /*!< Data type:   (char *)
                                                Description: File name reference to the document being parsed */

	motelDocumentMember_DocumentStream,        /*!< Data type:   (File *)
                                                Description: File or I/O stream handle to the document being parsed */

	motelDocumentMember_DocumentBuffer,        /*!< Data type:   (char *)
                                                Description: The document to parsed as a character buffer */

	motelDocumentMember_PublicID,              /*!< Data type:   (char *)
                                                Description: The public identifier for the current document event */

	motelDocumentMember_SystemID,              /*!< Data type:   (char *)
                                                Description: The system identifier for the current document event */

	motelDocumentMember_LineNumber,            /*!< Data type:   (long *)
                                                Description: The line number where the current document event ends */

	motelDocumentMember_ColumnNumber,          /*!< Data type:   (long *)
                                                Description: The column number where the current document event ends */

	motelDocumentMember_IgnoringElementContentWhitespace, /*!< Data type:   boolean
                                                           Description:  */

	motelDocumentCallback_StartDocument,       /*!< Data type:   (char *)
                                                Description:  */

	motelDocumentCallback_EndDocument,         /*!< Data type:   (char *)
                                                Description:  */

	motelDocumentCallback_StartPrefixMapping,  /*!< Data type:   (char *)
                                                Description:  */

	motelDocumentCallback_EndPrefixMapping,    /*!< Data type:   (char *)
                                                Description:  */

	motelDocumentCallback_StartObject,         /*!< Data type:   (char *)
                                                Description:  */

	motelDocumentCallback_EndObject,           /*!< Data type:   (char *)
                                                Description:  */

	motelDocumentCallback_Characters,          /*!< Data type:   (char *)
                                                Description:  */

	motelDocumentCallback_IgnorableWhitespace, /*!< Data type:   (char *)
                                                Description:  */

	motelDocumentCallback_ErrorHandler,        /*!< Data type:   (char *)
                                                Description:  */

	motelDocumentMember_Warning,               /*!< Data type:   boolean
                                                Description:  */

	motelDocumentMember_Error,                 /*!< Data type:   boolean
                                                Description:  */

	motelDocumentMember_FatalError,            /*!< Data type:   boolean
                                                Description:  */

	motelDocumentMember_Least,                 /*!< Data type:   NULL
                                                Description: Move the object cursor to lowest key value */

	motelDocumentMember_Greatest,              /*!< Data type:   NULL
                                                Description: Move the object cursor to greatest key value */

	motelDocumentMember_Lesser,                /*!< Data type:   NULL
                                                Description: Move the object cursor to next lower value */

	motelDocumentMember_Greater,               /*!< Data type:   NULL
                                                Description: Move the object cursor to next greater value */

	motelDocumentMember_Root,                  /*!< Data type:   NULL
                                                Description: Move the object cursor to the parse document root */

	motelDocumentMember_Parent,                /*!< Data type:   NULL
                                                Description: Move the object cursor to the current object's parent */

	motelDocumentMember_LesserChild,           /*!< Data type:   NULL
                                                Description: Move the object cursor to the current object's lesser child */

	motelDocumentMember_GreaterChild,          /*!< Data type:   NULL
                                                Description: Move the object cursor to the current object's greater child */

	motelDocumentMember_Head,                  /*!< Data type:   NULL
                                                Description: Set the object cursor to the head of the document */

	motelDocumentMember_Tail,                  /*!< Data type:   NULL
                                                Description: Set the object cursor to the tail of the document */

	motelDocumentMember_Previous,              /*!< Data type:   NULL
                                                Description: Move the object cursor toward the head of the document */

	motelDocumentMember_Next,                  /*!< Data type:   NULL
                                                Description: Move the object cursor toward the tail of the document */

	motelDocumentMember_
};

typedef struct motelDocumentNode motelDocumentNode;
typedef MUTABILITY motelDocumentNode * motelDocumentNodeHandle;

struct motelDocumentNode
{
    MUTABILITY motelDocumentNodeHandle parent;

	MUTABILITY motelDocumentNodeHandle lesser;

	MUTABILITY motelDocumentNodeHandle greater;

	MUTABILITY void * MUTABILITY name;
	MUTABILITY void * MUTABILITY value;
};

typedef struct motelDocument motelDocument;
typedef motelDocument * motelDocumentHandle;

struct motelDocument
{
	MUTABILITY motelResult result;

    MUTABILITY size_t maximumSize;
	MUTABILITY size_t size;
    
//    MUTABILITY motelCharacterMember character; /* document's character list */

    MUTABILITY motelHrrHandle documentHrr;
    MUTABILITY motelUrlHandle documentUrl;

    MUTABILITY motelFileHandle documentFile;

    MUTABILITY motelStreamHandle documentStream;
    MUTABILITY motelBufferHandle documentBuffer;

	MUTABILITY motelDocumentNodeHandle root;

	MUTABILITY motelDocumentNodeHandle cursor;
};

#endif