var express = require("express");
var router = express.Router();
const logsController = require("../controllers/logsController");

router.get("/history/:account_id", logsController.getLogs);
router.get("/:log_id", logsController.getById);

router.post("/", logsController.createLog);
router.delete("/:log_id", logsController.deleteLog);
router.put("/:log_id", logsController.updateLog);
router.get("/", logsController.getAll);

module.exports = router;
