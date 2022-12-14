// Messages sent from the server to the client

#pragma once

#include "lsptypes.h"
#include <string>

enum TextDocumentSyncKind {
    None = 0,
    Full = 1,
    Incremental = 2,
};

struct DidOpenTextDocumentParams {
    static constexpr std::string_view method = "textDocument/didOpen";
    /**
     * The document that was opened.
     */
    TextDocumentItem textDocument;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DidOpenTextDocumentParams, textDocument)

struct TextDocumentContentChangeEvent {
    Range range;
    Integer rangeLength;
    std::string text;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE_WITH_DEFAULT(TextDocumentContentChangeEvent,
                                                range,
                                                rangeLength,
                                                text);

struct DidChangeTextDocumentParams {
    /**
     * The document that did change. The version number points
     * to the version after all provided content changes have
     * been applied.
     */
    VersionedTextDocumentIdentifier textDocument;

    /**
     * The actual content changes. The content changes describe single state
     * changes to the document. So if there are two content changes c1 (at
     * array index 0) and c2 (at array index 1) for a document in state S then
     * c1 moves the document from S to S' and c2 from S' to S''. So c1 is
     * computed on the state S and c2 is computed on the state S'.
     *
     * To mirror the content of a document using change events use the following
     * approach:
     * - start with the same initial content
     * - apply the 'textDocument/didChange' notifications in the order you
     *   receive them.
     * - apply the `TextDocumentContentChangeEvent`s in a single notification
     *   in the order you receive them.
     */
    std::vector<TextDocumentContentChangeEvent> contentChanges;
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(DidChangeTextDocumentParams,
                                   textDocument,
                                   contentChanges);
