const account = require("../models/accountModel");
const card = require("../models/cardModel");

const getAll = (req, res) => {
  account.getAll((err, dbResult) => {
    if (err) {
      return res.status(500).send(err);
    }
    res.json(dbResult);
  });
};

const createAccount = (req, res) => {
  account.createAccount(req.body, (err, dbResult) => {
    if (err) {
      return res.send(err);
    }
    res.status(200).json({ message: "Account created" });
  });
};

const deleteAccount = (req, res) => {
  account.deleteAccount(req.params.account_id, (err, dbResult) => {
    if (err) {
      return res.send(err);
    }
    return res.status(200).json({ message: "Account deleted" });
  });
};

const updateAccount = (req, res) => {
  account.updateAccount(req.body, req.params.account_id, (err, dbResult) => {
    if (err) {
      return res.send(err);
    }
    return res.status(200).json({ message: "Account updated" });
  });
};

const getById = (req, res) => {
  account.getById(req.params.account_id, (err, dbResult) => {
    if (err) {
      return res.send(err);
    }
    res.json(dbResult[0]);
  });
};

const getBalance = (req, res) => {
  //console.log("fdgad");
  account.getBalance(req.cardId, (err, results) => {
    if (err) {
      return res.status(500).json(err);
    }
    return res.status(200).json(results);
  });
};

const withdraw = (req, res) => {
  //Check the type of card
  console.log(req.cardId);
  card.getType(req.cardId, (err, results) => {
    if (err) {
      return res.status(500).json(err);
    }
    //Makes negative amounts invalid
    if (req.body.amount < 0) {
      return res.status(400).json({ message: "Invalid amount" });
    }
    //Check if the card is a DEBIT card
    if (results[0].type === 0) {
      account.getBalance(req.cardId, (err, bResults) => {
        if (err) {
          return res.status(500).json(err);
        }
        //Check if the account has enough funds
        if (bResults[0].saldo_debit < req.body.amount) {
          return res.status(400).json({ message: "Insufficient funds" });
        }
        //Update the account
        account.updateDebit(
          req.body.amount,
          results[0].account_id,
          (err, results) => {
            if (err) {
              return res.status(500).json(err);
            }
            return res.status(200).json({ message: "Withdrawal successful" });
          }
        );
      });
    } else {
      account.getBalance(req.cardId, (err, bResults) => {
        if (err) {
          return res.status(500).json(err);
        }
        //Check if the account has enough funds
        if (bResults[0].saldo_credit < req.body.amount) {
          return res.status(400).json({ message: "Insufficient funds" });
        }
        //Update CREDIT account
        account.updateCredit(
          req.body.amount,
          results[0].account_id,
          (err, results) => {
            if (err) {
              return res.status(500).json(err);
            }
            return res.status(200).json({ message: "Withdrawal successful" });
          }
        );
      });
    }
  });
};


module.exports = {
  getAll,
  getById,
  getBalance,
  withdraw,
  createAccount,
  deleteAccount,
  updateAccount,
};
