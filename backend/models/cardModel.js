const database = require("../config/database");

const card = {
  getAll: function (callback) {
    return database.query("SELECT * FROM cards", callback);
  },
  getById: function (card_id, callback) {
    return database.query(
      "SELECT * FROM cards WHERE card_id = ?",
      [card_id],
      callback
    );
  },
  addCard: function (card, hash, callback) {
    return database.query(
      "INSERT into cards(number, pin, type, tries) values(?, ?, ?, 0);",
      [
        Math.floor(Math.random() * 899999999999 + 100000000000),
        hash,
        card.type,
      ],
      callback
    );
  },
  //getbyNumber Pietarin tekemä!
  getbyNumber: function (cardnumber, callback) {
    return database.query(
      "select * from cards where number = ?",
      [cardnumber],
      callback
    );
  },
  getType: function (cardId, callback) {
    return database.query(
      "SELECT type, account_id FROM cards WHERE card_id = ?",
      [cardId],
      callback
    );
  },
  deleteCard: function (card_id, callback) {
    return database.query(
      "DELETE FROM cards WHERE card_id = ?",
      [card_id],
      callback
    );
  },

  updateCard: function (card, card_id, callback) {
    return database.query(
      "UPDATE cards SET user_id = ?, account_id = ? WHERE card_id = ?",
      [card.user_id, card.account_id, card_id],
      callback
    );
  },
};

module.exports = card;
