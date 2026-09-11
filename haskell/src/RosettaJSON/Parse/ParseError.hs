module RosettaJSON.Parse.ParseError
    ( ParseError(..) ) where

data ParseError = EmptyString
                  | UnexpectedChar Char
                  | InvalidToken
                  deriving (Show)
