postInitialize
	^ self.

initialize
	^self initializeSupers postInitialize.

throwSender: senderName fails: methodName inClass: receiverName because: reason
| str |
    str := senderName, ' cannot send ',methodName asString,' to ',receiverName,' because: ' ,reason.
    AssertionFailure signal: str.