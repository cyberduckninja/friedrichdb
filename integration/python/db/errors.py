"""Exceptions raised by TinyMongo."""


class FriedrichError(Exception):
    """Base class for all TinyMongo exceptions."""


class ConnectionFailure(FriedrichError):
    """Raised when a connection to the database file cannot be made or is lost.
    """


class ConfigurationError(FriedrichError):
    """Raised when something is incorrectly configured.
    """


class OperationFailure(FriedrichError):
    """Raised when a database operation fails.
    """

    def __init__(self, error, code=None, details=None):
        self.__code = code
        self.__details = details
        FriedrichError.__init__(self, error)

    @property
    def code(self):
        """The error code returned by the server, if any.
        """
        return self.__code

    @property
    def details(self):
        """The complete error document returned by the server.

        Depending on the error that occurred, the error document
        may include useful information beyond just the error
        message. When connected to a mongos the error document
        may contain one or more subdocuments if errors occurred
        on multiple shards.
        """
        return self.__details


class CursorNotFound(OperationFailure):
    """Raised while iterating query results if the cursor is
    invalidated on the server.
    """


class WriteError(OperationFailure):
    """Base exception type for errors raised during write operations."""


class DuplicateKeyError(WriteError):
    """Raised when an insert or update fails due to a duplicate key error."""


class InvalidOperation(FriedrichError):
    """Raised when a client attempts to perform an invalid operation."""


class PyMongoError(Exception):
    """Base class for all PyMongo exceptions."""

    def __init__(self, message='', error_labels=None):
        super(PyMongoError, self).__init__(message)
        self._message = message
        self._error_labels = set(error_labels or [])

    def has_error_label(self, label):
        return label in self._error_labels

    def _add_error_label(self, label):
        """Add the given label to this error."""
        self._error_labels.add(label)

    def _remove_error_label(self, label):
        """Remove the given label from this error."""
        self._error_labels.discard(label)


class InvalidName(PyMongoError):
    """Raised when an invalid name is used."""
