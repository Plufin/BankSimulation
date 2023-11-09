const database = require("../config/database");

const account = {
  getAll: function (callback) {
    return database.query("SELECT * FROM accounts", callback);
  },

  createAccount: function (account, callback) {
    return database.query(
      "INSERT into accounts(user_id, saldo_debit, saldo_credit) values(?, ?, ?)",
      [account.user_id, account.saldo_debit, account.saldo_credit],
      callback
    );
  },

  deleteAccount: function (account_id, callback) {
    return database.query(
      "DELETE FROM accounts WHERE account_id = ?",
      [account_id],
      callback
    );
  },

  updateAccount: function (account, account_id, callback) {
    return database.query(
      "UPDATE accounts SET saldo_debit = ?, saldo_credit = ? WHERE account_id = ?",
      [account.saldo_debit, account.saldo_credit, account_id],
      callback
    );
  },

  getById: function (account_id, callback) {
    return database.query(
      "SELECT * FROM accounts WHERE account_id = ?",
      [account_id],
      callback
    );
  },
  getBalance: function (cardId, callback) {
    return database.query(
      "SELECT accounts.saldo_debit, accounts.saldo_credit FROM cards join accounts on accounts.account_id = cards.account_id WHERE cards.card_id = ?",
      [cardId],
      callback
    );
  },

  updateDebit: function (amount, account_id, callback) {
    return database.query(
      "UPDATE accounts SET saldo_debit = saldo_debit - ? WHERE account_id = ?",
      [amount, account_id],
      callback
    );
  },

  updateCredit: function (amount, account_id, callback) {
    return database.query(
      "UPDATE accounts SET saldo_credit = saldo_credit - ? WHERE account_id = ?",
      [amount, account_id],
      callback
    );
  },
};

module.exports = account;
