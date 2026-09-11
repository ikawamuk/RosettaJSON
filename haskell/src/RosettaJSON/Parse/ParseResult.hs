module RosettaJSON.Parse.ParseResult
    ( ParseError(..)
    , ParseResult
    ) where

import RosettaJSON.Types (JSONValue(..))

data ParseError = EmptyString
                  | UnexpectedChar Char
                  | InvalidToken
                  deriving (Show)

type ParseResult = Either ParseError (String, JSONValue)
