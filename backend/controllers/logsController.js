const logs = require("../models/logsModel");

const getLogs = (req, res) => {
  logs.getLogs(req.params.account_id, (err, dbResult) => {
    if (err) {
      return res.status(500).send(err);
    }
    return res.json(dbResult);
  });
};

const getById = (req, res) => {
  logs.getById(req.params.logs_id, (err, dbResult) => {
    if (err) {
      return res.send(err);
    }
    return res.json(dbResult[0]);
  });
};

const createLog = (req, res) => {
  logs.createLog(req.body, (err, dbResult) => {
    if (err) {
      return res.send(err);
    }
    return res.status(200).json({ message: "Log created" });
  });
};

const deleteLog = (req, res) => {
  logs.deleteLog(req.params.log_id, (err, dbResult) => {
    if (err) {
      return res.send(err);
    }
    return res.status(200).json({ message: "Log deleted" });
  });
};

const updateLog = (req, res) => {
  logs.updateLog(req.body, req.params.log_id, (err, dbResult) => {
    if (err) {
      return res.send(err);
    }
    return res.status(200).json({ message: "Log updated" });
  });
};

const getAll = (req, res) => {
  logs.getAll((err, dbResult) => {
    if (err) {
      return res.send(err);
    }
    return res.status(200).json(dbResult);
  });
};

module.exports = {
  getLogs,
  getById,
  createLog,
  deleteLog,
  updateLog,
  getAll,
};
