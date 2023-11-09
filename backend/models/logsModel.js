const database = require("../config/database");

const logs = {
  getLogs: function (account_id, callback) {
    return database.query(
      "SELECT date, event, amount FROM logs WHERE account_id = ? ORDER BY date DESC",
      [account_id],
      callback
    );
  },
  getById: function (log_id, callback) {
    return database.query(
      "SELECT * FROM logs WHERE log_id = ?",
      [log_id],
      callback
    );
  },
  createLog: function (data, callback) {
    return database.query(
      "INSERT INTO logs (account_id, event, amount) VALUES (?, ?, ?)",
      [data.account_id, data.event, data.amount],
      callback
    );
  },

  deleteLog: function (log_id, callback) {
    return database.query(
      "DELETE FROM logs WHERE log_id = ?",
      [log_id],
      callback
    );
  },
  updateLog: function (data, log_id, callback) {
    return database.query(
      "UPDATE logs SET event = ?, amount = ? WHERE log_id = ?",
      [data.event, data.amount, log_id],
      callback
    );
  },

  getAll: function (callback) {
    return database.query("SELECT * FROM logs", callback);
  },
};

module.exports = logs;
